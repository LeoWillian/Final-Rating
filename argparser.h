#pragma once
#include <QCommandLineParser>
#include <QScopedPointer>

QScopedPointer<QCommandLineParser> parse_args(const QCoreApplication& app);