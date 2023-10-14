#ifndef SAMLLOGINWINDOW_H
#define SAMLLOGINWINDOW_H

#include <QtCore/QMap>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QDialog>

#include "enhancedwebview.h"

class SAMLLoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SAMLLoginWindow(QString portal, QWidget *parent = nullptr);

    void login(const QString samlMethod, const QString samlRequest, const QString preloginUrl);
    QMap<QString, QString> loadCredentials();

signals:
    void success(QMap<QString, QString> samlResult);
    void fail(const QString code, const QString msg);

private slots:
    void onResponseReceived(QJsonObject params);
    void onLoadFinished();
    void checkSamlResult(QString username, QString preloginCookie, QString userAuthCookie);

private:
    static const auto MAX_WAIT_TIME { 10 * 1000 };

    bool failed { false };
    EnhancedWebView *webView { nullptr };
    QMap<QString, QString> samlResult;
    QString portal;

    void closeEvent(QCloseEvent *event);
    void handleHtml(const QString &html);

    static QString parseTag(const QString &tag, const QString &html);
};

#endif // SAMLLOGINWINDOW_H
