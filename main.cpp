#include <QApplication>
#include <QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWebView webView;

    webView.setWindowFlags(webView.windowFlags() | Qt::FramelessWindowHint);
    webView.load(QUrl::fromUserInput("google.com"));
    webView.show();

    return a.exec();
}
