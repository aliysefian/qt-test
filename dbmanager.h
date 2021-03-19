#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class DbManager
{
public:

     DbManager(const QString& path);

     ~DbManager();
     bool isOpen() const;

         /**
          * @brief Creates a new 'Users' table if it doesn't already exist
          * @return true - 'Users' table created successfully, false - table not created
          */
         bool createTable();

         /**
          * @brief fetch person data to db
          * @param pagesize- page size in each view ,current- the current page that is active
          * @return true - all user if search is ""
          */
         QSqlQuery getUserTable(const int& pagesize, const int& current, const QString &serach);

         /**
          * @brief Add person data to db
          * @param name - name of person to add
          * @return true - person added successfully, false - person not added
          */
         bool addPerson(const QString& name);

         /**
          * @brief Remove person data from db
          * @param name - name of person to remove.
          * @return true - person removed successfully, false - person not removed
          */
         bool removePerson(const QString& name);

         /**
          * @brief Check if person of name "name" exists in db
          * @param name - name of person to check.
          * @return true - person exists, false - person does not exist
          */
         bool personExists(const QString& name, const QString &password) const;

         /**
          * @brief Print names of all persons in db
          */
         void printAllPersons() const;

         /**
          * @brief Remove all persons from db
          * @return true - all persons removed successfully, false - not removed
          */
         bool removeAllPersons();


         /**
          * @brief get all Roles from db
          * @return QStringList- all Roles
          */
         QSqlQuery getAllRoles();
         /**
          * @brief Add Users data to db

          * @return true - users added successfully, false - users not added
          */
         bool addUser(const QString& name,const QString& password,
                      const int& role,const QString& expire_date,
                      const QString& description);
        QMap<QString,QString> getUser(QString id) const  ;



        QMap<QString,QString> UserExistWitdata(const QString& name, const QString &password, bool *exist)  ;

        /**
         * @brief  all count Users of  db
         * @param
         * @return  return all count Users of  db
         */
        QVariant countUser();

        /**
         * @brief  all count Users of  db
         * @param
         * @return  return all count Users of  db
         */
        bool updateUser(const QString &id, const QString& name,const QString& permission, const QString& password,
                            const int& role, const QString& expire_date,
                            const QString& description, const bool &isPaswordChangeMode);
        /**
         * @brief udate user last login
         * @param
         * @return  return true if is success
         */
        bool updateUserLastLoginDate(const QString &id);


private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
