//
//  HuPlayer.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuPlayer.h"
#include <stdio.h>
#include <sqlite3.h>
#include <CCFileUtils.h>
#include <sstream>

#define kCurrentPlayerIdKey "currentPlayerIdKey"

using namespace cocos2d;

HuPlayer* HuPlayer::mPInstance = NULL;

void HuPlayer::create()
{
    this->maxHealth = 100;
    this->health = this->maxHealth;
    this->currency = 50;
    // possibly start at level 0 as a demo or tutorial
    this->level = 1;
    this->name = "somebody i used to know";
    
    // base stuff
    this->baseHeight = 100;
    this->baseWidth = 100;
    this->defenseUpgradeLevel = DEFENSE_UPGRADE_0;
    
    // attack stuff
    this->attackWidth = 10;
    // TODO: this probably should be 100 to start out with
    this->damageModifier = 50;
    
    this->numberOfCannons = 0;
    this->numberOfSoldiers = 0;
    
    this->save();
}

static int sqlPrintCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static void setupDatabase()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
    std::string dbPath = fileUtils->getWritablePath();
    dbPath.append("HuData.db");
    
    rc = sqlite3_open(dbPath.c_str(), &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        
        const char *sql= "CREATE TABLE IF NOT EXISTS PLAYERS(" \
        "ID INT PRIMARY KEY NOT NULL, "\
        "NAME TEXT, " \
        "HEALTH INT, " \
        "MAXHEALTH INT, "\
        "CURRENCY INT, " \
        "LEVEL INT, " \
        "BASEWIDTH REAL, " \
        "BASEHEIGHT REAL, " \
        "ATTACKWIDTH  REAL, " \
        "DAMAGEMODIFIER INT, " \
        "NUMBEROFSOLDIERS INT, " \
        "NUMBEROFCANNONS INT, " \
        "DEFENSEUPGRADE INT)" \
        ";";
        
        rc = sqlite3_exec(db, sql,  sqlPrintCallback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stdout, "SQL Error: setupDatabase %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        
        sqlite3_close(db);
        
    }
    sqlite3_close(db);
}

void HuPlayer::save() {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kCurrentPlayerIdKey, playerID);
    CCUserDefault::sharedUserDefault()->flush();
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
    std::string dbPath = fileUtils->getWritablePath();
    dbPath.append("HuData.db");
    
    rc = sqlite3_open(dbPath.c_str(), &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        std::string sql = "INSERT OR REPLACE INTO PLAYERS (ID, NAME, HEALTH, MAXHEALTH, CURRENCY, LEVEL, BASEWIDTH, BASEHEIGHT, ATTACKWIDTH, DAMAGEMODIFIER, NUMBEROFSOLDIERS, NUMBEROFCANNONS, DEFENSEUPGRADE) VALUES (";
        std::stringstream ss;
        ss << playerID << ", ";
        ss << "\"" << name << "\", ";
        ss << health << ", ";
        ss << maxHealth << " ,";
        ss << currency << ", ";
        ss << level << ", ";
        ss << baseWidth << ", ";
        ss << baseHeight << ", ";
        ss << attackWidth << ", ";
        ss << damageModifier << ", ";
        ss << numberOfSoldiers << ", ";
        ss << numberOfCannons << ", ";
        ss << defenseUpgradeLevel << ");";
        sql.append(ss.str());
        
        
        fprintf(stdout, "sqlstring = %s\n", sql.c_str());
        
        rc = sqlite3_exec(db, sql.c_str(),  sqlPrintCallback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stdout, "SQL Error: saving player %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "SQL: saving player successful.\n");
        }
        
        sqlite3_close(db);
        
        
    }
    sqlite3_close(db);
}

static int sqlLoadCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc == 13) {
        HuPlayer *player = HuPlayer::getInstance();
        player->playerID = atoi(argv[0]);
        player->name = argv[1];
        player->health = atoi(argv[2]);
        player->maxHealth = atoi(argv[3]);
        player->currency = atoi(argv[4]);
        player->level = atoi(argv[5]);
        player->baseWidth = atof(argv[6]);
        player->baseHeight = atof(argv[7]);
        player->attackWidth = atof(argv[8]);
        player->damageModifier = atof(argv[9]);
        player->numberOfSoldiers = atoi(argv[10]);
        player->numberOfCannons = atoi(argv[11]);
        player->defenseUpgradeLevel = (PlayerDefenseUpgrade)atoi(argv[12]);
        
        // just always set health to maxhealth on load
        player->health = player->maxHealth;
        
    } else {
        fprintf(stdout, "Error: sqlite load callback incorrect number of arguments = %d\n", argc);
    }
    int i;
    for(i=0; i<argc; i++){
        fprintf(stdout, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool HuPlayer::loadPlayerWithID(int playerID)
{
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
    std::string dbPath = fileUtils->getWritablePath();
    dbPath.append("HuData.db");
    
    rc = sqlite3_open(dbPath.c_str(), &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
        return false;
    }else{
        fprintf(stderr, "Opened database successfully\n");
        char sqlbuffer[200];
        int n = sprintf(sqlbuffer, "SELECT * FROM PLAYERS WHERE ID = %d;", playerID);
        if (n > 200) {
            fprintf(stdout, "SQL: save player sqlbuffer overflow\n");
            return false;;
        }
        
        
        rc = sqlite3_exec(db, sqlbuffer,  sqlLoadCallback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stdout, "SQL Error: saving player %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        } else {
            fprintf(stdout, "SQL: saving player successful.\n");
        }
        
        sqlite3_close(db);
        
        
    }
    sqlite3_close(db);

    return true;
}

int HuPlayer::currentPlayerID()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(kCurrentPlayerIdKey);
}

bool HuPlayer::loadLastPlayer() {
    
    return HuPlayer::loadPlayerWithID(currentPlayerID());
    
}

HuPlayer *HuPlayer::getInstance() {
    if (!mPInstance) {
        mPInstance = new HuPlayer;
        setupDatabase();
        loadLastPlayer();
    }
    
    return mPInstance;
}

