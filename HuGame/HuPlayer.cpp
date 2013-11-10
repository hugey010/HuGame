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

#define kCurrentPlayerIdKey "currentPlayerIdKey"

using namespace cocos2d;

HuPlayer* HuPlayer::mPInstance = NULL;

HuPlayer *HuPlayer::getInstance() {
    if (!mPInstance) {
        mPInstance = new HuPlayer;
        setupDatabase();
    }
    
    
    return mPInstance;
}

void HuPlayer::create()
{
    this->health = 100;
    this->currency = 50;
    // possibly start at level 0 as a demo or tutorial
    this->level = 1;
    this->name = CCStringMake("myname");
    
    // base stuff
    this->baseHeight = 100;
    this->baseWidth = 100;
    
    // attack stuff
    this->attackWidth = 50;
    // TODO: this probably should be 100 to start out with
    this->damageModifier = 100;
    
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
    rc = sqlite3_open("data.db", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
        
        const char *sql= "CREATE TABLE IF NOT EXISTS PLAYERS(" \
        "ID INT PRIMARY KEY NOT NULL, "\
        "NAME TEXT, " \
        "HEALTH INT, " \
        "CURRENCY INT, " \
        "LEVEL INT, " \
        "BASEWIDTH REAL, " \
        "BASEHEIGHT REAL, " \
        "ATTACKWIDTH  REAL, " \
        "DAMAGEMODIFIER INT)" \
        ";";
        
        rc = sqlite3_exec(db, sql,  sqlPrintCallback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stdout, "SQL Error: setupDatabase %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "SQL: database setup successful.\n");
        }
        
        sqlite3_close(db);
        
        
    }
    sqlite3_close(db);
}

void HuPlayer::save() {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kCurrentPlayerIdKey, playerID);
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("data.db", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
        char sqlbuffer[200];
        int n = sprintf(sqlbuffer, "INSERT OR REPLACE INTO PLAYERS (ID, NAME, HEALTH, CURRENCY, LEVEL, BASEWIDTH, BASEHEIGHT, ATTACKWIDTH, DAMAGEMODIFIER) VALUES (%d, %s, %d, %d, %d, %f, %f, %f, %d);", playerID, name->getCString(), health, currency, level, baseWidth, baseHeight, attackWidth, damageModifier);
        if (n > 200) {
            fprintf(stdout, "SQL: save player sqlbuffer overflow\n");
            return;
        }
        
        
        rc = sqlite3_exec(db, sqlbuffer,  sqlPrintCallback, 0, &zErrMsg);
        
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
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static void loadPlayerWithPlayerID(int playerID)
{
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("data.db", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
        char sqlbuffer[200];
        int n = sprintf(sqlbuffer, "SELECT * FROM PLAYERS WHERE ID = %d;", playerID);
        if (n > 200) {
            fprintf(stdout, "SQL: save player sqlbuffer overflow\n");
            return;
        }
        
        
        rc = sqlite3_exec(db, sqlbuffer,  sqlLoadCallback, 0, &zErrMsg);
        
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

static int currentPlayerID()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(kCurrentPlayerIdKey);
}

static void loadLastPlayer() {
    
    loadPlayerWithPlayerID(currentPlayerID());
    
}

