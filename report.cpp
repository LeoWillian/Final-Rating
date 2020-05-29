#include "report.h"
#include "errors.h"

#include <math.h>

void Report::useStrategy(QString course, QStringList criteria, QVector <report>& student_main) {
     return operation->use(course,criteria, student_main);
}

void Report::setStrategy(std::unique_ptr <Strategy>& o) {
    operation = move(o);
}

//начало сортировки
bool sort_id_ascending(const report& a, const report& b) {
    return a.id < b.id;
} 

//сортировка по id
bool sort_id_descending(const report& a, const report& b) {
    return a.id > b.id;
} 

//сортировка по имени
bool sort_name_ascending(const report& a, const report& b) {
    return a.name < b.name;
} 

bool sort_name_descending(const report& a, const report& b) {
    return a.name > b.name;
} 

//сортировка по посещаемости
bool sort_attendance_ascending(const report& a, const report& b) {
    return a.attendance < b.attendance;
} 

bool sort_attendance_descending(const report& a, const report& b) {
    return a.attendance > b.attendance;
} 

//сортировка по активности
bool sort_plus_ascending(const report& a, const report& b) {
    return a.test < b.test;
}

bool sort_plus_descending(const report& a, const report& b) {
    return a.test > b.test;
}

//сортировка по оценке за тест(если был)
bool sort_test_ascending(const report& a, const report& b) {
    return a.test < b.test;
}

bool sort_test_descending(const report& a, const report& b) {
    return a.test > b.test;
} 

//сортировка по рейтингу
bool sort_rating_ascending(const report& a, const report& b) {
    return a.average_rating < b.average_rating;
}

bool sort_rating_descending(const report& a, const report& b) {
    return a.average_rating > b.average_rating;
}

void Report::sorting(QVector <report>& student_main, QMap <QString, QString> sort_fld) {
    //выбор поля, по которому пользователь хочет отсортировать
    foreach (QString str, sort_fld.keys()) {
        if (str == "id"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_id_descending);
            else qSort(student_main.begin(), student_main.end(), sort_id_ascending);
        }

        else if (str == "name"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_name_descending);
            else qSort(student_main.begin(), student_main.end(), sort_name_ascending);
        }

        else if (str == "attendance"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_attendance_descending);
            else qSort(student_main.begin(), student_main.end(), sort_attendance_ascending);
        }

        else if (str == "plus"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_plus_descending);
            else qSort(student_main.begin(), student_main.end(), sort_plus_ascending);
        }

        else if (str == "test"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_test_descending);
            else qSort(student_main.begin(), student_main.end(), sort_test_ascending);
        }

        else if (str == "rating"){
            if (sort_fld.value(str) == "descending")
                qSort(student_main.begin(), student_main.end(), sort_rating_descending);
            else qSort(student_main.begin(), student_main.end(), sort_rating_ascending);
        }
    }
}

const void Report::report_output(QVector <report>& student_main, bool table, QStringList split_criteries) {

    for (int i = 0; i < student_main.size(); i++) 
        if (student_main[i].attendance == -1 && student_main[i].plus == -1 && 
        student_main[i].test == -1 && student_main[i].average_rating == -1) 
            student_main.erase(student_main.begin()+i);
    //построение таблицы
    if(table) {
        std::cout << '\t' << "Name" << '\t' << "|" << '\t' << "Rating" << '\t' << "|"; 
        for (int i = 0; i < split_criteries.size(); i++) 
            std::cout << '\t' << split_criteries[i].toStdString() << '\t' << "|";
        std::cout << std::endl;
        for (int i = 0; i < student_main.size(); i++) {
            std::cout  << student_main[i].name.toStdString() << '\t' << "|" << '\t' << std::setprecision(3) << student_main[i].average_rating << '\t' << "|";
            for (int j = 0; j < split_criteries.size(); j++) {
                
                if (split_criteries[j] == "plus") std::cout << '\t' << std::setprecision(3) << student_main[i].plus << '\t' << "|";
                if (split_criteries[j] == "test") std::cout << '\t' << std::setprecision(3) << student_main[i].test << '\t' << "|";
                if (split_criteries[j] == "attendance") std::cout << '\t' << std::setprecision(3) << student_main[i].attendance << '\t' << '\t' << "|";
            }
            std::cout << std::endl;
        }
    }
    else {
        for (int i = 0; i < student_main.size(); i++) {
            std::cout << i+1 << ") " << student_main[i].name.toStdString() << " ";
            std::cout << '(';
            for (int j = 0; j < split_criteries.size(); j++) {
                if (split_criteries[j] == "test") std::cout << "test: " << std::setprecision(3) << student_main[i].test;
                if (split_criteries[j] == "plus") std::cout << "plus: " << std::setprecision(3) << student_main[i].plus;
                if (split_criteries[j] == "attendance") std::cout << "attendance: " << std::setprecision(3) << student_main[i].attendance;
                if (j != split_criteries.size()-1) std::cout << ", ";
            }
            std::cout << ')';
            std::cout << std::endl;
        }
    }
}
