#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMap>

static const QString pathreal = "/home/ali/QT/QTsqlAPP/project.db";

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(pathreal);


   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}


DbManager::~DbManager()
{

    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare(
                "create table users"
                  "(                      id                   integer not null"
                 "         constraint users_pk"
                          "    primary key autoincrement,"
                    "  username             varchar(50),"
                    "  password             varchar(200),"
                 "     role_id              integer"
                      "    references roles"
                           "   on update cascade on delete cascade,"
                    "  permission           int default 1.84467440737096e+19,"
                   "   register_date        datetime,"
                    "  password_expire_date datetime,"
                    "  last_login_date      datetime,"
                   "   description          varchar"
              "    );"

              "    create unique index users_id_uindex"
                    "  on users (id);"
            );

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}

QSqlQuery DbManager::getUserTable(const int& pagesize=10,const int& current=1,const QString& serach="")
{
    qDebug() << "Users in db:";

    QSqlQuery query;

//        query.prepare("SELECT * from users where username like %:username% limit (:pagesize) offset (:offset)");


        query.prepare("SELECT * from users where username like '%"+serach+"%' " );

//        query.bindValue(":serach", serach);
        query.bindValue(":pagesize", pagesize);
        query.bindValue(":offset", ((current-1)*pagesize));



    if(query.exec())
    {  qDebug() << "add person sucesss" ;
    }
    else
    {
        qDebug() << "add person failed: " << query.lastError();
    }

    qDebug() << "last"<<query.lastQuery();
    return query;
}

bool DbManager::addPerson(const QString& name)
{
    bool success = false;

    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO users (name) VALUES (:name)");
        queryAdd.bindValue(":name", name);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}
bool DbManager::addUser(const QString& name, const QString& password, const int& role, const QString &expire_date, const QString &description)
{
    bool success = false;

    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO users (username,password,role_id,register_date,password_expire_date,description) VALUES "
                         "((:name),(:password),(:role_id),datetime('now', 'localtime'),:password_expire_date,:description)");
        queryAdd.bindValue(":name", name);
        queryAdd.bindValue(":password", password);
        queryAdd.bindValue(":role_id",role);
        queryAdd.bindValue(":password_expire_date",expire_date);
         queryAdd.bindValue(":description",description);
        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removePerson(const QString& name)
{
    bool success = false;

//    if (personExists(name))
//    {
    QSqlQuery queryDelete;
    queryDelete.prepare("DELETE FROM users WHERE id = (:name)");
    queryDelete.bindValue(":name", name);
    success = queryDelete.exec();

    if(!success)
    {
        qDebug() << "remove person failed: " << queryDelete.lastError();
    }
//    }
//    else
//    {
//        qDebug() << "remove person failed: person doesnt exist";
//    }

    return success;
}

void DbManager::printAllPersons() const
{
    qDebug() << "Persons in db:";
    QSqlQuery query("SELECT * FROM users");


    int idName = query.record().indexOf("username");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}
QMap<QString, QString> DbManager::getUser(QString id) const
{
    qDebug() << "usersssssssss in db:"<<id.toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM users where (id=:ids)");
    query.bindValue(":ids",id);
    QMap<QString, QString> data;

        if (query.exec())
        {
            int idName = query.record().indexOf("id");
            int idUsername = query.record().indexOf("username");
            int idExpierDate = query.record().indexOf("password_expire_date");
            int idRoleId = query.record().indexOf("role_id");
            int idPermission = query.record().indexOf("permission");
            int idDescription = query.record().indexOf("description");
            int idPassowrd = query.record().indexOf("password");



            if (query.next())  data.insert("username",query.value(idUsername).toString() );
            {
                 data.insert("id",query.value(idName).toString() );
                 data.insert("password",query.value(idPassowrd).toString() );
                 data.insert("password_expire_date",query.value(idExpierDate).toString() );
                 data.insert("username",query.value(idUsername).toString() );
                 data.insert("role_id",query.value(idRoleId).toString() );
                 data.insert("permission",query.value(idPermission).toString() );
                 data.insert("description",query.value(idDescription).toString() );

                qDebug() << "===" << data;
            }
        }
        else
        {
            qDebug() << "person exists failed: " << query.lastError();
        }

            return data;

}

QMap<QString, QString> DbManager::UserExistWitdata(const QString &name, const QString &password,bool* exist)
{

        QSqlQuery query;
        query.prepare("SELECT id, username FROM users where username=:username and password=:password");
        query.bindValue(":username",name);
        query.bindValue(":password",password);

        QMap<QString, QString> data;

            if (query.exec())
            {
                int idName = query.record().indexOf("id");
                int idUsername = query.record().indexOf("username");


                if (query.next())
                {
                     data.insert("id",query.value(idName).toString() );
                     data.insert("username",query.value(idUsername).toString() );
                     *exist=true;
                     qDebug() << "===" << data;
                }
            }
            else
            {
                qDebug() << "Users exists failed: " << query.lastError();
            }
            return data;
}

QVariant DbManager::countUser()
{

    QSqlQuery query;
    query.prepare("SELECT count(*) as count FROM users");
    QVariant count;
        if (query.exec())
        {
            int idCount = query.record().indexOf("count");

            if (query.next())
            {
                count=query.value(idCount);

                qDebug() << "===" << query.value(idCount);
            }
        }
        else
        {
            qDebug() << "no data found  " << query.lastError();
        }

        return count;

}
bool DbManager::updateUser(const QString& id,const QString& name,const QString& permission,const QString& password,
                           const int& role,const QString& expire_date,
                           const QString& description,const bool& isPaswordChangeMode)
{
    bool success = false;
    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        if(isPaswordChangeMode){
            queryAdd.prepare("update users set (username,password,permission,role_id,password_expire_date,description)  "
                             " = ((:name),(:password),:permission,(:role_id),:password_expire_date,:description)"
                             "where id=:id");
            queryAdd.bindValue(":id", id);
            queryAdd.bindValue(":name", name);
            queryAdd.bindValue(":password", password);
            queryAdd.bindValue(":role_id",role);
            queryAdd.bindValue(":password_expire_date",expire_date);
            queryAdd.bindValue(":description",description);
            queryAdd.bindValue(":permission", permission);
        }
        else{
            queryAdd.prepare("update users set (username,permission,role_id,password_expire_date,description)  "
                             " = ((:name),:permission,(:role_id),:password_expire_date,:description)"
                             "where id=:id");
            queryAdd.bindValue(":id", id);
            queryAdd.bindValue(":name", name);

            queryAdd.bindValue(":role_id",role);
            queryAdd.bindValue(":password_expire_date",expire_date);
            queryAdd.bindValue(":description",description);
            queryAdd.bindValue(":permission", permission);

        }
        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;

}

bool DbManager::updateUserLastLoginDate(const QString &id)
{
    bool success = false;

        QSqlQuery queryAdd;
        int ids=id.toInt();
        queryAdd.prepare("update users set (last_login_date) = datetime('now', 'localtime') where id="+id);
//        queryAdd.bindValue(":ids", ids);

        if(queryAdd.exec())
        {
             qDebug() <<"ttttttttttttttttt"<<queryAdd.executedQuery();
            success = true;
        }
        else
        {
            qDebug() << "update failed: " << queryAdd.lastError();
        }


    return success;

}



bool DbManager::personExists(const QString& name,const QString& password) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM users WHERE username= (:name) and password=:pass");
    checkQuery.bindValue(":name", name);
    checkQuery.bindValue(":pass", password);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllPersons()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM people");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}

QSqlQuery DbManager::getAllRoles()
{
    qDebug() << "Roles in db:";
    QSqlQuery query("SELECT id,name FROM Roles");
    int idName = query.record().indexOf("name");
    return query;
}
