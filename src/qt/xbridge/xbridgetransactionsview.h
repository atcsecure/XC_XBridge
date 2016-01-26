//******************************************************************************
//******************************************************************************

#ifndef XBRIDGETRANSACTIONSVIEW_H
#define XBRIDGETRANSACTIONSVIEW_H

#include "xbridge/xbridgetransactionsmodel.h"
#include "xbridge/xbridgetransactiondialog.h"

#include "../walletmodel.h"

#include <QWidget>
#include <QMenu>
#include <QSortFilterProxyModel>

class QTableView;

//******************************************************************************
//******************************************************************************
class XBridgeTransactionsView : public QWidget
{
    Q_OBJECT
public:
    explicit XBridgeTransactionsView(QWidget *parent = 0);
    ~XBridgeTransactionsView();

public:
    void setWalletModel(WalletModel * model);

signals:

public slots:

private:
    void setupUi();
    QMenu * setupContextMenu(QModelIndex & index);

private slots:
    void onNewTransaction();
    void onAcceptTransaction();
    void onCancelTransaction();
    void onRollbackTransaction();

    void onContextMenu(QPoint pt);

private:
    WalletModel            * m_walletModel;

    XBridgeTransactionsModel m_txModel;
    QSortFilterProxyModel    m_proxy;

    XBridgeTransactionDialog m_dlg;

    QTableView  * m_transactionsList;

    QModelIndex   m_contextMenuIndex;
};

#endif // XBRIDGETRANSACTIONSVIEW_H
