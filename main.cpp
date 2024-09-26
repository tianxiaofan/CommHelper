/**************************************************************************
 *   文件名	：%{Cpp:License:FileName}
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2024-9-26
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：西安英杰伟成航空科技有限公司
 *   功能描述      ：
 *   使用说明 ：任何人或机构要使用、修改、发布本源代码,都必须要获得西安英杰伟成航空科技有限公司的授权
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CommHelper", "Main");

    return app.exec();
}
