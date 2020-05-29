#include "correct.h"
#include "errors.h"

#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

QStringList main_file_list(QString trail) {

    QString s="";
    QDir dir(trail);
    bool flag = dir.exists();
    if (flag) {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo info = list.at(i);
            s+=info.fileName()+" ";
        }
    }
    QStringList ans = s.split(".json ");
    return ans;
}
//добавление данных о студенте по выбранной дате в файл курса
void addition_prs(QString course, QString criteria, QString student_name, QString date) { 
    QStringList split_criteries;
    if (!criteria.isEmpty())
        split_criteries = criteria.split(",");
    else split_criteries.push_back("attendance");
    
    QStringList course_list;
    if (course == ".json") { 
        course_list = main_file_list(QDir::homePath() + "/.students-rating/courses");
        std::cout <<"Select a course (1-" << course_list.size() - 1 << "):" << std::endl;
        for (int i = 0; i < course_list.size()-1; ++i) {
            std::cout << i + 1 << ". " << course_list[i].toStdString() << std::endl;        
        }
        int choice;
        std::cin >> choice;
        qDebug() << "Chosen course: " << course_list[choice - 1];
        course = course_list[choice - 1] + ".json";
    }
    
    QStringList group_list = main_file_list(QDir::homePath() + "/.students-rating/groups");
    std::cout <<"Select a group (1-" << group_list.size() - 1 << "):" << std::endl;
    for (int i = 0; i < group_list.size()-1; ++i) {
        std::cout << i + 1 << ". " << group_list[i].toStdString() << std::endl;        
    }
    int choice;
    std::cin >> choice ;
    qDebug() << "Selected group: " << group_list[choice - 1];
    QString group;
    group = group_list[choice - 1] + ".json";
        
    QStringList list_choice; 
    QStringList student_list;
    if (student_name.isEmpty()) {
        std::ifstream in((QDir::homePath()+ "/.students-rating/groups/" + group).toStdString());
        json group_json;
        in >> group_json;
        in.close(); 
        for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {
            student_list.push_back(QString::fromStdString(it.value()["name"]));
        } 
        std::cout << "Select students with a space (1-" << student_list.size() << "):" << std::endl;
        for (int i = 0; i < student_list.size(); ++i) {
            std::cout << i + 1 << ". " << student_list[i].toStdString() << std::endl;    
        }
        std::cin.get();
        std::string choice;
        getline(std::cin, choice);
        list_choice = QString::fromStdString(choice).split(" ");
    }

    if (date.isEmpty()) {
        std::cout << "Enter the date(press 'Enter' if it is today date): " << std::endl;
        std::string today_date;
        getline(std::cin, today_date);
        if (today_date.empty()) {
            QDate cd = QDate::currentDate();
            date =  cd.toString(Qt::ISODate);
        }
        else date = QString::fromStdString(today_date);        
        date.replace("-","/");
        qDebug() << "Selected date: " << date;
    }

    std::ifstream in((QDir::homePath()+"/.students-rating/courses/" + course).toStdString());
    json course_json;
    in >> course_json;
    in.close();

    std::ifstream in1((QDir::homePath()+"/.students-rating/groups/" + group).toStdString());
    json group_json;
    in1 >> group_json;
    in1.close();
    for (int i = 0; i < list_choice.size(); ++i) {
        int id;
        for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {   
            if (student_list[list_choice[i].toInt() - 1].toStdString() == it.value()["name"]) {
                id = it.value()["id"];
                break;
            }
        }
        for (json::iterator it = course_json["progress"].begin(); it != course_json["progress"].end(); ++it) {
            if (QString::fromStdString(it.key()) == QString::number(id)) {
                it.value()[date.toStdString()];
                for (int j = 0; j < split_criteries.size(); j++) {
                    if (split_criteries[j] == "attendance") {
                        std::cout << "Student name: " << student_list[list_choice[i].toInt()-1].toStdString() << std::endl; 
                        std::cout << "Select the student attendance (1 or 2): " << std::endl;
                        std::cout << "1. True." << std::endl;
                        std::cout << "2. False." << std::endl;
                        int choice;
                        std::cin >> choice;
                        if (choice == 1)    
                            it.value()[date.toStdString()][split_criteries[j].toStdString()] = true;
                        else it.value()[date.toStdString()][split_criteries[j].toStdString()] = false;
                    }

                    if (split_criteries[j] == "test") {
                        std::cout << "Student name: " << student_list[list_choice[i].toInt()-1].toStdString() << std::endl;
                        std::cout << "Enter the test score : " << std::endl;
                        double rating_test;
                        std::cin >> rating_test;
                        it.value()[date.toStdString()][split_criteries[j].toStdString()] = rating_test;
                    }
                    
                    if (split_criteries[j] == "plus") {
                        int choice;
                        std::cout << "Student name: " << student_list[list_choice[i].toInt()-1].toStdString() << std::endl;
                        std::cout << "Input plus (1 or 2): " << std::endl;
                        std::cout << "1. True." << std::endl;
                        std::cout << "2. False." << std::endl;
                        std::cin >> choice;
                        if (choice == 1)    
                            it.value()[date.toStdString()][split_criteries[j].toStdString()] = true;
                        else it.value()[date.toStdString()][split_criteries[j].toStdString()] = false;
                    }
                    
                    if (split_criteries[j] == "assignment") {
                        int choice;
                        std::cout << "Student name: " << student_list[list_choice[i].toInt()-1].toStdString() << std::endl; 
                        std::cout << "Input assignment (1 or 2): " << std::endl;
                        std::cout << "1. True." << std::endl;
                        std::cout << "2. False." << std::endl;
                        std::cin >> choice;
                        if (choice == 1)    
                            it.value()[date.toStdString()][split_criteries[j].toStdString()] = true;
                        else it.value()[date.toStdString()][split_criteries[j].toStdString()] = false;
                    } 
                }
            }     
        }
    }
    std::ofstream out((QDir::homePath()+"/.students-rating/courses/" + course).toStdString());
    out << std::setw(4) << course_json << std::endl;
    out.close();
}
//добавление студента в выбранный курс
void addition_student(QString group, QString student_name, QString course) {

    QStringList course_list;
    if (course == ".json") { 
        course_list = main_file_list(QDir::homePath() + "/.students-rating/courses");
        //микросчетчик курсов, чтобы было понятно откуда до куда выбирать
        std::cout << "Select a course (1-" << course_list.size()-1 << "): " << std::endl;
        //вывод всех курсов из списка курсов
        for (int i = 0; i < course_list.size() - 1; i++) {
            std::cout << i + 1 << ". " << course_list[i].toStdString() << std::endl;        
        }
        int choice;
        std::cin >> choice;
        //вывод выбранного пользователем курса
        qDebug() << "Chosen course: " << course_list[choice-1];
        course = course_list[choice - 1] + ".json";
    }

    if (group == ".json") {
        QStringList group_list = main_file_list(QDir::homePath()+"/.students-rating/groups");
        std::cout <<"Select a group (1-" << group_list.size()-1 << "):" << std::endl;
        for (int i = 0; i < group_list.size() - 1; ++i) {
            std::cout << i + 1 << ". " << group_list[i].toStdString() << std::endl;        
        }
        int choice;
        std::cin >> choice;
        qDebug() << "Selected group: " << group_list[choice-1];
        group = group_list[choice - 1] + ".json";
    }

    if (student_name.isEmpty()) {
        std::cout << "Input student name : " << std::endl;
        std::string student; 
        std::cin.get();
        getline(std::cin, student);
        student_name = QString::fromStdString(student);
    }
    //занос в тег "students" id и имени
    std::ifstream in((QDir::homePath() + "/.students-rating/groups/" + group).toStdString());
    json group_json;
    in >> group_json;
    in.close();
    int max_id = group_json["students"][0]["id"];
    for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {   
        if (it.value()["id"] > max_id )
            max_id = it.value()["id"];
    }
    //присваивание текущего id+1(максимального, следующего по счету)
    group_json["students"] += {{"id", max_id + 1},{"name", student_name.toStdString()}};
    std::ofstream o((QDir::homePath() + "/.students-rating/groups/" + group).toStdString());
    o << std::setw(4) << group_json << std::endl;
    o.close();

    std::ifstream in1((QDir::homePath() + "/.students-rating/courses/" + course).toStdString());
    json course_json;
    in1 >> course_json;
    
    QString id1 = QString::number(max_id + 1);
    std::string id = id1.toStdString();
    course_json["progress"] += json::object_t::value_type(id, nullptr);
    std::ofstream o1((QDir::homePath()+"/.students-rating/courses/" + course).toStdString());
    o1 << std::setw(4) << course_json << std::endl;
    in1.close();
    o1.close();
    std::cout << "Added!" << std::endl;
}
//Добавление курса
void addition_course(QString course) {
    auto trail = (QDir::homePath() + "/.students-rating/courses/" + course).toStdString();
    std::ofstream o(trail);
    o.close();
    std::cout << "Do you want add: group and students? (1 or 2):" << std::endl;
    std::cout << "1. Yes." << std::endl;
    std::cout << "2. No." << std::endl;
    int choice;
    std::cin >> choice;
    //обработка выбора Yes
    if (choice == 1) {

        //выбор группы
        QStringList list_choice; 
        QString group;
        QStringList group_list = main_file_list(QDir::homePath()+"/.students-rating/groups");
        std::cout <<"Select a group (1-" << group_list.size() - 1 << "):" << std::endl;
        for (int i = 0; i < group_list.size() - 1; ++i) {
            std::cout << i + 1 << ". " << group_list[i].toStdString() << std::endl;        
        }
        int choice;
        std::cin >> choice ;
        qDebug() << "Selected group: " << group_list[choice - 1];
        group = group_list[choice - 1];

        //выбор студента
        QStringList student_list;      
        std::ifstream in((QDir::homePath() + "/.students-rating/groups/" + group + ".json").toStdString());
        json group_json;
        in >> group_json;
        in.close(); 
        for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {
            student_list.push_back(QString::fromStdString(it.value()["name"]));
        } 
        std::cout << "Select the student(s) separated by a space (1-" << student_list.size() << "):" << std::endl;
        for (int i = 0; i < student_list.size(); ++i) {
            std::cout << i + 1 << ". " << student_list[i].toStdString() << std::endl;    
        }
        std::cin.get();
        std::string choice1;
        getline(std::cin, choice1);
        list_choice = QString::fromStdString(choice1).split(" ");
        //занос студента в группу и курс, соответствующий этой группе
        json course_json;    
        
        course_json["group"] = group.toStdString();
        course_json["progress"] = nullptr;

        for (int i = 0; i < list_choice.size(); ++i) {
            int id;
            for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {   
                if (student_list[list_choice[i].toInt()-1].toStdString() == it.value()["name"]) {
                    id = it.value()["id"];
                    break;
                }
            }
            QString id_temp = QString::number(id);
            std::string id_fin = id_temp.toStdString();
            course_json["progress"] += json::object_t::value_type(id_fin, nullptr);
        }
        std::ofstream out((QDir::homePath()+"/.students-rating/courses/" + course).toStdString());
        out << std::setw(4) << course_json << std::endl;
        out.close();
    }
}

//корректировка имени
// void correct_name(std::string id, QString group) {
//     auto trail = (QDir::homePath() + "/.students-rating/groups/" + group).toStdString();
//     std::ifstream in(trail);
//     json group_json;
//     in >> group_json;
    
//     for (json::iterator it = group_json["students"].begin(); it != group_json["students"].end(); ++it) {
//         if (it.value()["id"] == atoi(id.c_str())) {
//             std::cout << "Student found!" << std::endl;
//             std::cout << it.value()["name"] << " change to: ";
//             std::string correct_name;
//             getline( std::cin, correct_name);
//             it.value()["name"] = correct_name;
//             break;
//         }
//     }

//     std::ofstream out(trail);
//     out << std::setw(4) << group_json << std::endl;
//     in.close();
//     out.close();
// }
// //корректировка посещаемости
// void correct_attend(std::string id, QString course) {
//     auto trail = (QDir::homePath()+ "/.students-rating/courses/" + course).toStdString();
//     std::ifstream in(trail);
//     json course_json;
//     in >> course_json;

//     for (json::iterator it = course_json["progress"].begin(); it != course_json["progress"].end(); ++it) {
//         if (it.key() == id) {
//             std::cout << "Enter the date to correct: ";
//             std::string date;
//             std::cin >> date;
//             bool flag = false;
//             for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); ++it1) {

//                 if (it1.key() == date) {
//                     flag = true;
//                     std::cout << "Did the student attend the lesson?(1 or 2)"<< std::endl;
//                     std::cout << "--> 1.Yes."<< std::endl;
//                     std::cout << "--> 2.No." << std::endl;
//                     int res;
//                     std::cin >> res;
//                     if (res == 1) {
//                         it1.value()["attendance"] = true;
//                         std::cout << "Was there a test on this lesson? (1 or 2)"<< std::endl;
//                         std::cout << "--> 1.Yes."<< std::endl;
//                         std::cout << "--> 2.No." << std::endl;
//                         int main_test;
//                         std::cin >> main_test;
//                         if (main_test == 1) {
//                             std::cout << "What grade did the student get for the test?: ";
//                             //вводим оценку
//                             double rating_test;
//                             std::cin >> rating_test;
//                             it1.value()["test"] = rating_test;
//                         }
//                         if (main_test == 2) it1.value().erase("test");
//                         std::cout << "Did the student on this pair receive a plus?" << std::endl;
//                         std::cout << "--> 1.Yes."<< std::endl;
//                         std::cout << "--> 2.No." << std::endl;
//                         int main_plus;
//                         std::cin >> main_plus;
//                         if (main_plus == 1) it1.value()["plus"] = true;
//                         if (main_plus == 2) it1.value()["plus"] = false;
//                     }
//                     //в случае отсутствия студента автоматически посещение ложно, аналогично и активность на паре
//                     if (res == 2) {
//                         it1.value()["attendance"] = false;
//                         it1.value().erase("plus");
//                         std::cout << "Was there a test in this lesson?"<< std::endl;
//                         std::cout << "--> 1.Yes."<< std::endl;
//                         std::cout << "--> 2.No." << std::endl;
//                         int main_test;
//                         std::cin >> main_test;
//                         if (main_test == 1) it1.value()["test"] = 0;
//                         //убираем поле тест из курса
//                         if (main_test == 2) it1.value().erase("test");
//                     }
//                 }                
//             }       
//             if (!flag)
//                 std::cout << "The date is not found! Please try again." << std::endl;
//         }
//     }
//     std::ofstream out(trail);
//     out << std::setw(4) << course_json << std::endl;
//     in.close();
//     out.close();
// }

// //удаление студента
// void remove_student(std::string id, QString object) {
//     auto trail = (QDir::homePath()+"/.students-rating/courses/" + object).toStdString();
//     std::ifstream in(trail);
//     json course_json;
//     in >> course_json;
//     in.close();

//     course_json["progress"].erase(id);

//     std::ofstream out(trail);
//     out << std::setw(4) << course_json << std::endl;
//     out.close();
//     std::cout << "Succes!" << std::endl;
// }