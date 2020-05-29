#include "argparser.h"
#include "errors.h"

#include <QCoreApplication>

QScopedPointer<QCommandLineParser> parse_args(const QCoreApplication& app) {

    auto parser = new QCommandLineParser;

    parser->setApplicationDescription("Students rating app.");
    parser->addHelpOption();

    parser->addOption({
        "report",
        "Building a report"
    });

    parser->addOption({
        {"course", "c"},
        "Choice a course",
        "text"
    });

    parser->addOption({
        {"criteria", "r"},
        "Choice a criteria",
        "TEXT"
    });

    parser->addOption({
        {"table", "t"},
        "Table view of data",
    });
    
    parser->addOption({
        {"sort", "s"},
        "Sort data.",
        "TEXT",
        "rating=desc"
    });

    parser->addOption({
        {"date", "d"},
        "Date lesson",
        "text"
    });

    parser->addOption({
        "id",
        "Student id",
        "text"
    });

    parser->addOption({
        "group",
        "Student group",
        "text"
    });

    parser->addOption({
        "add-progress",
        "Add student performance"
    });

    parser->addOption({
        {"student-name", "n"},
        "Student name",
        "text"
    });

    parser->addOption({
        "add-student",
        "Add student"
    });

    parser->addOption({
        "add-course",
        "Add course"
    });

    //  parser->addOption({
    //     "correct-name",
    //     "Correct student name from group file"
    // });

    // parser->addOption({
    //     "correct-attendance",
    //     "Correct student attendance from course file"
    // });

    //   parser->addOption({
    //     "remove-student",
    //     "Remove student from file"
    // });

    parser->process(app);

    if (!parser->parse(QCoreApplication::arguments()))
        error(parser->errorText().toLatin1().toStdString());

    return QScopedPointer(parser);
}