#include <QApplication>
#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QUdpSocket>
#include <QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Bind the receive socket.
    QUdpSocket recvSocket;

    recvSocket.bind(QHostAddress::LocalHost, 5498);

    // Serialize the URL and send the datagram.
    const QString sendUrl("google.com");
    QByteArray sendDatagram;
    QDataStream sendStream(&sendDatagram, QIODevice::WriteOnly);
    QUdpSocket sendSocket;

    sendStream << sendUrl;
    sendSocket.writeDatagram(sendDatagram, QHostAddress::LocalHost, 5498);

    // Receive the datagram.
    QByteArray recvDatagram;

    recvSocket.waitForReadyRead();
    recvDatagram.resize(recvSocket.pendingDatagramSize());
    recvSocket.readDatagram(recvDatagram.data(), recvDatagram.size());

    // Deserialize the URL.
    QDataStream recvStream(recvDatagram);
    QString recvUrl;

    recvStream >> recvUrl;

    Q_ASSERT(sendUrl == recvUrl);

    // Open the URL received from the client.
    QWebView webView;
    webView.setWindowFlags(webView.windowFlags() | Qt::FramelessWindowHint);
    webView.load(QUrl::fromUserInput(recvUrl));
    webView.show();

    return a.exec();
}
