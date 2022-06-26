using namespace std;

void print()
{
    cout << "welcome!" << endl;
}

/*
Function name: callback
Author: Zhao Haochen
Features: enabling cmd operations
*/
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/*
Function name: initUser()
Author: Zhao Haochen
Features: creating a database with table 'Events'
*/
bool initUser()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open SQL database */
    rc = sqlite3_open("userEvents.db", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create SQL statement */
    sql = "CREATE TABLE Events("
          "ID INT PRIMARY KEY     NOT NULL,\n"
          "DATE           CHAR(11)    NOT NULL,\n"
          "TOPIC            CHAR(20)     NOT NULL,\n"
          "EVENT        CHAR(50)    NOT NULL,\n"
          "DESCRIPTION  CHAR(100),\n"
          "DDL         CHAR(11) \n);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
    return 1;
}

/*
Function name: addEvent()
Author: Zhao Haochen
Features: adding a record to the exsisting table, consisting of ID, DATE, TOPIC, EVENT, DESCRIPTION, and DDL
*/
bool addEvent()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create SQL statement */
    sql = "INSERT INTO Events (ID,DATE,TOPIC,EVENT,DESCRIPTION,DDL) "
          "VALUES (2, '2022-05-04', 'PE', 'pull-ups X15', 'very hard', '2022-06-04' ); ";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 1;
}

/*
Function name: showEvent()
Author: Zhao Haochen
Features: showing all information in the existing table
*/
bool showEvent()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create SQL statement */
    sql = "SELECT * from Events";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    fprintf(stdout, "Operation done successfully\n");
    sqlite3_close(db);
    return 1;
}

/*
Function name: searchEvent_topic
Author: Zhao Haochen
Features: searching corresponding records according to the topic typed by the user
*/
bool searchEvent_topic()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create SQL statement */
    sql = "SELECT * from Events where TOPIC = 'PE'";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    fprintf(stdout, "Operation done successfully\n");
    sqlite3_close(db);
    return 1;
}

/*
Function name: searchEvent_ddl
Author: Zhao Haochen
Features: searching corresponding records according to the ddl typed by the user
*/
bool searchEvent_ddl()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create SQL statement */
    sql = "SELECT * from Events where DDL = '2022-06-04'";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    fprintf(stdout, "Operation done successfully\n");
    sqlite3_close(db);
    return 1;
}


/*
Function name: deleteEvent()
Author: Zhao Haochen
Features: searching and deleting a specific record in the table
*/
bool deleteEvent()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create merged SQL statement */
    sql = "DELETE from Events where ID=2; "
          "SELECT * from Events";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    fprintf(stdout, "Operation done successfully\n");
    sqlite3_close(db);
    return 1;
}

/*
Function name: editEvent()
Author: Zhao Haochen
Features: searching and editing a record from the table
*/
bool editEvent()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("userEvents.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    fprintf(stderr, "Opened database successfully\n");

    /* Create merged SQL statement */
    sql = "UPDATE Events set DDL = '2022-06-15' where ID=1; "
          "SELECT * from Events";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    fprintf(stdout, "Operation done successfully\n");
    sqlite3_close(db);
    return 1;
}