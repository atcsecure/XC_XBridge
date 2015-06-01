//******************************************************************************
//******************************************************************************

#ifndef XBRIDGECONNECTOR_H
#define XBRIDGECONNECTOR_H

#include "xbridgepacket.h"
#include "xbridgelowlevel.h"
#include "xbridgetransaction.h"
#include "wallet.h"

#include <boost/thread/mutex.hpp>


//******************************************************************************
//******************************************************************************
class XBridgeConnector : public XBridgeLowLevel
{
    friend XBridgeConnector & xbridge();

private:
    XBridgeConnector();

private:
    virtual void handleTimer();

public:
    bool announceLocalAddresses();
    bool sendXChatMessage(const Message & m);

    uint256 sendXBridgeTransaction(const std::vector<unsigned char> & from,
                                   const std::string & fromCurrency,
                                   const boost::uint64_t fromAmount,
                                   const std::vector<unsigned char> & to,
                                   const std::string & toCurrency,
                                   const boost::uint64_t toAmount);
    bool revertXBridgeTransaction(const uint256 & id);

    bool transactionReceived(const uint256 & hash);

private:
    CScript destination(const std::vector<unsigned char> & address);
    bool sendCancelTransaction(const std::vector<unsigned char> & hub,
                               const uint256 & txid);

    std::string txToString(const CTransaction & tx) const;
    CTransaction txFromString(const std::string & str) const;

private:
    bool processInvalid(XBridgePacketPtr packet);
    bool processXChatMessage(XBridgePacketPtr packet);

    bool processExchangeWallets(XBridgePacketPtr packet);

    bool processTransactionHold(XBridgePacketPtr packet);
    bool processTransactionInit(XBridgePacketPtr packet);
    bool processTransactionCreate(XBridgePacketPtr packet);
    bool processTransactionSign(XBridgePacketPtr packet);
    bool processTransactionCommit(XBridgePacketPtr packet);
    // bool processTransactionConfirm(XBridgePacketPtr packet);
    bool processTransactionFinished(XBridgePacketPtr packet);
    bool processTransactionCancel(XBridgePacketPtr packet);
    bool processTransactionDropped(XBridgePacketPtr packet);

private:
    boost::mutex                             m_txLocker;
    std::map<uint256, XBridgeTransactionPtr> m_pendingTransactions;
    std::map<uint256, XBridgeTransactionPtr> m_transactions;

    std::set<uint256> m_receivedTransactions;
};

//******************************************************************************
//******************************************************************************
XBridgeConnector & xbridge();

#endif // XBRIDGECONNECTOR_H