#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "board.h"
#include "musicplayer.h"
#include "mynetwork.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/chess/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Board chessBoard;
    engine.rootContext()->setContextProperty("chessBoard", &chessBoard);
    Board netChessBoard;
    engine.rootContext()->setContextProperty("netChessBoard", &netChessBoard);

    qmlRegisterType<MyNetWork>("MyNetWork", 1, 0, "Ipv4");

    //创建音乐播放器并设置为QML上下文属性，没有使用QML是因为会闪退
    // MusicPlayer musicPlayer;
    // engine.rootContext()->setContextProperty("musicPlayer", &musicPlayer);

    engine.load(url);
    return app.exec();
}
