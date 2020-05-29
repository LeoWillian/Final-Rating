#pragma once

#include <memory>
#include <iomanip>  
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

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
#include <QTextStream>
#include <QDate>

void addition_prs(QString course, QString criteria, QString student_name, QString date);
void addition_student(QString group, QString student_name, QString course);
void addition_course(QString course);
// void correct_name(std::string id, QString group);
// void correct_attend(std::string id, QString course);
// void remove_student(std::string id, QString object);


