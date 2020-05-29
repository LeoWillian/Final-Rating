#pragma once

#include <string>
#include <memory>
#include <iomanip>  

#include "strategy.h"

#include <QtAlgorithms>

class Report {

public:
    void useStrategy(QString course, QStringList criteria, QVector <report>& student_main);
    void setStrategy(std::unique_ptr <Strategy>& o);
    void sorting(QVector <report>& student_main, QMap <QString, QString> sort_fld);  
    const void report_output(QVector <report>& student_main, bool table, QStringList split_criteries);
private:
    std::unique_ptr <Strategy> operation;
};