#include "errors.h"
#include "strategy.h"

#include <nlohmann/json.hpp>

#include <chrono>
#include <random>
#include <stdexcept>
#include <map>
#include <fstream>

using json = nlohmann::json;

//добавление критерий
void addition_criteria(QString id, QVector <report>& student_main, double attendance, double test, double plus, double average_rating) {

    for (int i = 0; i < student_main.size(); i++) {
        if (student_main[i].id == id) {   
        student_main[i].attendance += attendance == -1 ? 0 : attendance + 1;
        student_main[i].test += test == -1 ? 0 : test + 1;
        student_main[i].plus += plus == -1 ? 0 : plus + 1;
        student_main[i].average_rating += average_rating == -1 ? 0 : average_rating + 1;
        }
    }
}

void filling_in_data(json in_course, QVector <report>& student_main) {

    std::string group = in_course["group"].get<std::string>();
    auto trail = (QDir::homePath()+"/.students-rating/groups/" + QString::fromStdString(group) + ".json").toStdString();
    std::ifstream in(trail);
    json group_json;
    in >> group_json;
    in.close();
    for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); it++) {
        int id = it.value()["id"];
        report status(QString::fromStdString(it.value()["name"]), QString::number(id) , -1, -1, -1, -1);
        student_main.push_back(status);
    } 
}

void AverageRating::use(QString course, QStringList criteria, QVector <report>& student_main) {
    
    for (int i = 0; i < student_main.size(); i++) {
        student_main[i].average_rating = (student_main[i].plus + student_main[i].attendance + student_main[i].test) / 3;
    }
}

void Attendance::use(QString course, QStringList criteria, QVector <report>& student_main) {

    double count = 0;
    double attend = 0;
    auto trail = (QDir::homePath()+"/.students-rating/courses/" + course).toStdString();
    std::ifstream in(trail);
    json in_course ;
    in >> in_course;
    in.close();
    if (student_main.empty())
        filling_in_data(in_course, student_main);  
    for (json::iterator it = in_course["progress"].begin(); it != in_course["progress"].end(); it++) {
        QString id = QString::fromStdString(it.key());
        for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); it1++) {
            count++;
            if (it1.value()["attendance"] == true)
                attend++;
        }
        addition_criteria(id, student_main, attend / count, -1, -1, -1);
    }
}

void Test::use(QString course, QStringList criteria, QVector <report>& student_main) {

    double count = 0;
    double total = 0;
    auto trail = (QDir::homePath()+"/.students-rating/courses/" + course).toStdString();
    std::ifstream in(trail);
    json in_course ;
    in >> in_course;
    in.close();
    if (student_main.empty())
        filling_in_data(in_course, student_main); 
    for (json::iterator it = in_course["progress"].begin(); it != in_course["progress"].end(); it++) {
        QString id = QString::fromStdString(it.key());
        for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); ++it1) {
            if (it1.value()["test"] != nullptr) {
                count++;
                total += it1.value()["test"].get<double>();
            }   
        }
        addition_criteria(id, student_main, -1, total / 5 * count, -1, -1);
    }
}

void Plus::use(QString course, QStringList criteria, QVector <report>& student_main) {

    double count = 0;
    double cnt_plus = 0;
    auto trail = (QDir::homePath()+"/.students-rating/courses/" + course).toStdString();
    std::ifstream in(trail);
    json in_course ;
    in >> in_course;
    in.close();
    if (student_main.empty())
         filling_in_data(in_course, student_main); 
    for (json::iterator it = in_course["progress"].begin(); it != in_course["progress"].end(); it++) {
        QString id = QString::fromStdString(it.key());
        for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); ++it1) {
            count++;
            if (it1.value()["plus"] == true)
                cnt_plus++;
        }
       addition_criteria(id, student_main, -1, -1, cnt_plus / count, -1);
    }
    
}