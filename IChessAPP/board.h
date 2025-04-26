#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>

#include "pieces.h"

class Board : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role { PieceImgRole = Qt::UserRole };
    enum Player { WhitePlayer, BlackPlayer, waitPlayer };

    Board();
    virtual ~Board();

    // 判断黑白方
    Player colortoPlayer(Pieces::Color color);
    Q_INVOKABLE QString getTurn();

    // 晋升相关
    Q_INVOKABLE void setPromotion(QString promotion);
    Q_INVOKABLE void changeType(int x, int y);

    // 初始化棋子
    QVector<QSharedPointer<Pieces>> initPieces();

    // 重置model数据
    Q_INVOKABLE void reset();

    // QAbstractListModel的虚函数，用于提供模型数据
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // 王车易位相关
    void autoMoveRook(int fromX, int fromY, int toX, int toY);

    // 移动
    Q_INVOKABLE void move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE QVector<int> possibleMoves(int x, int y);

    //悔棋
    Q_INVOKABLE void regretChess();

    //设置轮次（主要用于联机）
    Q_INVOKABLE void setWhitePlayer();
    Q_INVOKABLE void setBlackPlayer();
    Q_INVOKABLE void setWaitPlayer();

signals:
    void whiteWin();
    void blackWin();
    void promote();

private:
    QVector<QSharedPointer<Pieces>> m_pieces;

    Player turn;

    QString m_promotion;

    QVector<QSharedPointer<Pieces>> m_record;
};
