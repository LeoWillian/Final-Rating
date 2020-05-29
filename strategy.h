#pragma once

#include <QMap>
#include <QDebug>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QScopedPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QVector>

#include <iostream>

struct report {
public:

    QString id;
    QString name;
    double attendance;
    double test;
    double plus;
    double average_rating;

    report(QString name_student, QString id_student, double attendance_student, double plus_student, double test_student, double average_rating_student) {
        id = id_student; name = name_student;
        attendance = attendance_student; test = test_student; plus = plus_student;
        average_rating  = average_rating_student;
    }
    
    report() {}
};

class Strategy {
public:
    virtual ~Strategy() {}
    virtual void use(QString course, QStringList criteria, QVector <report>& student_main) = 0;
};

class Attendance: public Strategy {
public:  
    void use(QString course, QStringList criteria, QVector <report>& student_main);
};

class Plus: public Strategy {
public:    
    void use(QString course, QStringList criteria, QVector <report>& student_main);
};

class Test: public Strategy {
public: 
    void use(QString course, QStringList criteria, QVector <report>& student_main);
};

class AverageRating: public Strategy {
public:
    void use(QString course, QStringList criteria, QVector <report>& student_main);
};
