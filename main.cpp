#include "errors.h"
#include "argparser.h"
#include "report.h"
#include "strategy.h"
#include "correct.h"

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
#include <QtAlgorithms>

#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <fstream>
#include <memory>
#include <iomanip>  

using namespace std;

void finish_rep(QString course, QString criteria, bool table, QString sort_order) {

    //исключение для критерий
    if (criteria == "") error("Please input criteria");
    //исключение для курса 
    if (course == ".json") error("Please input course.");
    //исключение для формата сортировки
    if (sort_order == "") error("Please input sort mods");

    QStringList split_sort_order = sort_order.split(",");
    QMap <QString, QString> sort_order_main;
    for (int i = 0; i < split_sort_order.length(); i++) {
        QStringList spit_sample = split_sort_order[i].split("=");
        sort_order_main.insert(spit_sample[0],spit_sample[1]);
    }   

    QVector <report> student_main;   
    Report report_student;
    QStringList split_criteries = criteria.split(",");
    unique_ptr <Strategy> strategy;
    strategy = make_unique <Attendance>();
    report_student.setStrategy(strategy);
    report_student.useStrategy(course, split_criteries, student_main);

    strategy = make_unique <Plus>();
    report_student.setStrategy(strategy);
    report_student.useStrategy(course, split_criteries, student_main);

    strategy = make_unique <Test>();
    report_student.setStrategy(strategy);
    report_student.useStrategy(course, split_criteries, student_main);

    strategy = make_unique <AverageRating>();
    report_student.setStrategy(strategy);
    report_student.useStrategy(course, split_criteries, student_main);
    report_student.sorting(student_main, sort_order_main);
    
    report_student.report_output(student_main, table, split_criteries);
   
}

int main(int argc, char** argv) {
    try {   

        auto parser = parse_args(QCoreApplication(argc, argv));  

        string argument = argv[1];

        if (argument == "report") {
            auto course = parser->value("course") + ".json";
            auto criteria = parser->value("criteria");
            auto table = parser->isSet("table") ? true: false;
            auto sort_order = parser->value("sort");
            finish_rep(course, criteria, table, sort_order);
        }

        // if (argument == "correct-name") {
        //     auto id = parser->value("id").toStdString();
        //     auto group = parser->value("group") + ".json";
        //     correct_name(id, group);
        // }

        // if (argument == "correct-attendance") {
        //     auto id = parser->value("id").toStdString();
        //     auto course = parser->value("course") + ".json";
        //     correct_attend(id, course);
        // }

        if (argument == "add-progress") {
            auto course = parser->value("course") + ".json";
            auto criteria = parser->value("criteria");
            auto student_name = parser->value("student-name");
            auto date = parser->value("date");
            addition_prs(course, criteria, student_name, date);
        }

        if (argument == "add-student") {
            auto group = parser->value("group") + ".json";
            auto student_name = parser->value("student-name");
            auto course = parser->value("course") + ".json";
            addition_student(group, student_name, course);
        }

        if (argument == "add-course") {
            auto course = QString::fromStdString(argv[2]) + ".json";
            addition_course(course);
        }

        // if (argument == "remove-student") {
        //     auto id = parser->value("id").toStdString();
        //     auto course = parser->value("course") + ".json";
        //     remove_student(id, course);
        // }

    }
    catch (const exception& ex) {
        cout << "ERROR: " << ex.what() << endl;
    }  
}