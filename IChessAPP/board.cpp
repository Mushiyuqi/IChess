#include "board.h"

Board::Board()
    : m_pieces(initPieces())
    , turn(WhitePlayer)
{}

Board::~Board() {}

void Board::reset()
{
    beginResetModel();
    m_pieces = initPieces(); // 重新初始化棋子
    m_record = {};           // 清空记录
    turn = WhitePlayer;      // 重置回合为白方
    qDebug() << "reset";
    endResetModel();
}
Board::Player Board::colortoPlayer(Pieces::Color color)
{
    switch (color) {
    case Pieces::White:
        return WhitePlayer;
    case Pieces::Black:
        return BlackPlayer;
    }
}

QString Board::getTurn()
{
    if (turn == WhitePlayer) {
        return "white";
    } else if (turn == BlackPlayer) {
        return "black";
    }

    return "wait";
}

void Board::setPromotion(QString promotion)
{
    m_promotion = promotion;
}

void Board::changeType(int x, int y)
{
    QSharedPointer<Pieces> p;
    int i;

    for (i = 0; i < m_pieces.length(); ++i) {
        p = m_pieces[i];
        if (p->x() == x && p->y() == y) {
            qDebug() << "该棋子在m_pieces[i]里的索引为i: " << i;
            break; // 找到当前棋子
        }
    }

    // 变换棋子类型的思路：
    // 1.创建一个新的棋子
    // 2.在vector最后加入新棋子
    // 3.将位于末尾的新棋子与索引为i的棋子交换位置
    // 4.删除末尾的棋子(即原来的棋子)

    if (m_promotion == "queen") {
        // 新的后
        QSharedPointer<Pieces> newQueen{new Queen{x, y, p->color(), p->id()}};

        m_pieces.append(newQueen);
        m_pieces[i].swap(m_pieces.last());
        m_pieces.pop_back();
        qDebug() << "change to queen";
    } else if (m_promotion == "rook") {
        // 新的车
        QSharedPointer<Pieces> newRook{new Rook{x, y, p->color(), p->id()}};

        m_pieces.append(newRook);
        m_pieces[i].swap(m_pieces.last());
        m_pieces.pop_back();
        qDebug() << "change to rook";
    } else if (m_promotion == "knight") {
        // 新的马
        QSharedPointer<Pieces> newKnight{new Knight{x, y, p->color(), p->id()}};

        m_pieces.append(newKnight);
        m_pieces[i].swap(m_pieces.last());
        m_pieces.pop_back();
        qDebug() << "change to knight";
    } else if (m_promotion == "bishop") {
        // 新的象
        QSharedPointer<Pieces> newbishop{new Bishop{x, y, p->color(), p->id()}};

        m_pieces.append(newbishop);
        m_pieces[i].swap(m_pieces.last());
        m_pieces.pop_back();
        qDebug() << "change to bishop";
    }

    QModelIndex index = createIndex(y * 8 + x, 0);
    emit dataChanged(index, index);
}

QVector<QSharedPointer<Pieces>> Board::initPieces()
{
    QVector<QSharedPointer<Pieces>> pieces
        = {// 黑
           QSharedPointer<Pieces>{new Rook{0, 0, Pieces::Black, 0}},
           QSharedPointer<Pieces>{new Knight{1, 0, Pieces::Black, 1}},
           QSharedPointer<Pieces>{new Bishop{2, 0, Pieces::Black, 2}},
           QSharedPointer<Pieces>{new Queen{3, 0, Pieces::Black, 3}},
           QSharedPointer<Pieces>{new King{4, 0, Pieces::Black, 4}},
           QSharedPointer<Pieces>{new Bishop{5, 0, Pieces::Black, 5}},
           QSharedPointer<Pieces>{new Knight{6, 0, Pieces::Black, 6}},
           QSharedPointer<Pieces>{new Rook{7, 0, Pieces::Black, 7}},
           QSharedPointer<Pieces>{new Pawn{0, 1, Pieces::Black, 8}},
           QSharedPointer<Pieces>{new Pawn{1, 1, Pieces::Black, 9}},
           QSharedPointer<Pieces>{new Pawn{2, 1, Pieces::Black, 10}},
           QSharedPointer<Pieces>{new Pawn{3, 1, Pieces::Black, 11}},
           QSharedPointer<Pieces>{new Pawn{4, 1, Pieces::Black, 12}},
           QSharedPointer<Pieces>{new Pawn{5, 1, Pieces::Black, 13}},
           QSharedPointer<Pieces>{new Pawn{6, 1, Pieces::Black, 14}},
           QSharedPointer<Pieces>{new Pawn{7, 1, Pieces::Black, 15}},
           // 白
           QSharedPointer<Pieces>{new Pawn{0, 6, Pieces::White, 16}},
           QSharedPointer<Pieces>{new Pawn{1, 6, Pieces::White, 17}},
           QSharedPointer<Pieces>{new Pawn{2, 6, Pieces::White, 18}},
           QSharedPointer<Pieces>{new Pawn{3, 6, Pieces::White, 19}},
           QSharedPointer<Pieces>{new Pawn{4, 6, Pieces::White, 20}},
           QSharedPointer<Pieces>{new Pawn{5, 6, Pieces::White, 21}},
           QSharedPointer<Pieces>{new Pawn{6, 6, Pieces::White, 22}},
           QSharedPointer<Pieces>{new Pawn{7, 6, Pieces::White, 23}},
           QSharedPointer<Pieces>{new Rook{0, 7, Pieces::White, 24}},
           QSharedPointer<Pieces>{new Knight{1, 7, Pieces::White, 25}},
           QSharedPointer<Pieces>{new Bishop{2, 7, Pieces::White, 26}},
           QSharedPointer<Pieces>{new Queen{3, 7, Pieces::White, 27}},
           QSharedPointer<Pieces>{new King{4, 7, Pieces::White, 28}},
           QSharedPointer<Pieces>{new Bishop{5, 7, Pieces::White, 29}},
           QSharedPointer<Pieces>{new Knight{6, 7, Pieces::White, 30}},
           QSharedPointer<Pieces>{new Rook{7, 7, Pieces::White, 31}}};

    return pieces;
}

int Board::rowCount(const QModelIndex &parent) const
{
    return 8 * 8;
}

QVariant Board::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row() / 8; // 行，对应y
    int col = index.row() % 8; // 列，对应x

    switch (role) {
    case PieceImgRole: {
        QString src = QString("qrc:/img/");

        for (int i = 0; i < m_pieces.length(); ++i) {
            auto p = m_pieces[i];
            if (p->x() == col && p->y() == row) {
                switch (p->type()) {
                case Pieces::king:
                    src.append("king");
                    break;

                case Pieces::queen:
                    src.append("queen");
                    break;

                case Pieces::rook:
                    src.append("rook");
                    break;

                case Pieces::knight:
                    src.append("knight");
                    break;

                case Pieces::bishop:
                    src.append("bishop");
                    break;

                case Pieces::pawn:
                    src.append("pawn");
                    break;
                default:
                    break;
                }
                switch (p->color()) {
                case Pieces::White:
                    src.append("-white.svg");
                    return src;
                case Pieces::Black:
                    src.append("-black.svg");
                    return src;
                default:
                    break;
                }
            }
        }

    } break;
    }

    return QVariant();
}

QHash<int, QByteArray> Board::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PieceImgRole] = "pieceImg";
    return roles;
}

void Board::autoMoveRook(int fromX, int fromY, int toX, int toY)
{
    QSharedPointer<Pieces> p, prev;

    for (int i = 0; i < m_pieces.length(); ++i) {
        p = m_pieces[i];
        if (p->x() == fromX && p->y() == fromY && p->type() == Pieces::rook) {
            break; // 找到当前棋子
        }
    }
    prev.reset(new Rook{p->x(), p->y(), p->color(), p->id()});
    m_record.append(prev);
    p->setX(toX);
    p->setY(toY);
    p->setFirstMove(false);

    // createIndex创建并返回一个 QModelIndex 对象，该对象指向模型中移动后的位置
    QModelIndex fromIndex = createIndex(fromY * 8 + fromX, 0);
    QModelIndex toIndex = createIndex(toY * 8 + toX, 0);

    // dataChanged是QAbstractItemModel的一个信号，通知界面更新棋子的位置
    // 两个参数都是newIndex，意味着只通知了一个数据项的改变，用于单个数据项的更新
    emit dataChanged(fromIndex, fromIndex);
    emit dataChanged(toIndex, toIndex);
}

void Board::setBlackPlayer()
{
    if (turn == BlackPlayer) {
        return;
    } else {
        turn = BlackPlayer;
    }
}
void Board::setWhitePlayer()
{
    if (turn == WhitePlayer) {
        return;
    } else {
        turn = WhitePlayer;
    }
}
void Board::setWaitPlayer()
{
    if (turn == waitPlayer) {
        return;
    } else
        turn = waitPlayer;
}

void Board::move(int fromX, int fromY, int toX, int toY)
{
    QSharedPointer<Pieces> p, tmp, prev;
    bool isEmpty = true;

    for (int i = 0; i < m_pieces.length(); ++i) {
        p = m_pieces[i];
        if (p->x() == fromX && p->y() == fromY) {
            break; // 找到当前棋子
        }
    }

    if (turn != colortoPlayer(p->color())) {
        return;
    }

    for (int i = 0; i < m_pieces.length(); ++i) {
        tmp = m_pieces[i];
        if (tmp->x() == toX && tmp->y() == toY) {
            isEmpty = false;
            break; // 找到当前棋子
        }
        tmp = nullptr;
    }

    if (isEmpty) {
        // 选中的位置没有棋子

        // 王车易位在这里！！！！！！王动了之后自动变换车的位置
        if (p->type() == Pieces::king && p->color() == Pieces::Black) {
            // 短易位
            if ((toY * 8 + toX) == 6) {
                autoMoveRook(7, 0, 5, 0);
                qDebug() << "王车易位了！！！";
            }

            // 长易位
            if ((toY * 8 + toX) == 2) {
                autoMoveRook(0, 0, 3, 0);
                qDebug() << "王车易位了！！！";
            }
        } else if (p->type() == Pieces::king && p->color() == Pieces::White) {
            // 短易位
            if ((toY * 8 + toX) == 62) {
                autoMoveRook(7, 7, 5, 7);
                qDebug() << "王车易位了！！！";
            }

            // 长易位
            if ((toY * 8 + toX) == 58) {
                autoMoveRook(0, 7, 3, 7);
                qDebug() << "王车易位了！！！";
            }
        }

        // 设置第一次移动
        if (p->isFirstMove()) {
            p->setFirstMove(false);
        }
    } else if (!isEmpty && p->color() != tmp->color()) {
        // 选中的位置有敌方棋子

        switch (tmp->type()) {
        case Pieces::pawn:
            prev.reset(new Pawn{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        case Pieces::bishop:
            prev.reset(new Bishop{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        case Pieces::knight:
            prev.reset(new Knight{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        case Pieces::rook:
            prev.reset(new Rook{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        case Pieces::queen:
            prev.reset(new Queen{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        case Pieces::king:
            prev.reset(new King{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
            break;
        default:
            break;
        }
        m_record.append(prev);
        qDebug() << "吃子后---m_record.length(): " << m_record.length();

        // 选中的是王
        if (tmp->type() == Pieces::king) {
            if (tmp->color() == Pieces::White) {
                emit blackWin();
                return;
            } else if (tmp->color() == Pieces::Black) {
                emit whiteWin();
                return;
            }
        }

        // 该棋子被移除
        for (int i = 0; i < m_pieces.length(); ++i) {
            if (m_pieces[i]->id() == tmp->id()) {
                m_pieces.remove(i);
                qDebug() << "removed---该棋子在m_pieces[i]里的索引为i: " << i
                         << "id: " << tmp->id();
                qDebug() << "m_pieces.length(): " << m_pieces.length();
            }
        }
    }

    // 兵升变(晋升)
    if (p->type() == Pieces::pawn) {
        if (p->color() == Pieces::White && toY == 0) {
            emit promote();
        } else if (p->color() == Pieces::Black && toY == 7) {
            emit promote();
        }
    }

    // 吃过路兵
    // 这里移动过后，敌方兵被吃，自动消失
    if (p->type() == Pieces::pawn) {
        if (p->color() == Pieces::White && toY == 2) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == toX && tmp->y() == toY + 1 && tmp->type() == Pieces::pawn
                    && tmp->color() == Pieces::Black) {
                    isEmpty = false;
                    break; // 找到(toX, toY)的下方有黑兵
                }
                tmp = nullptr;
            }
            if (!isEmpty) {
                // (toX, toY)的下方的黑兵被移除
                for (int i = 0; i < m_pieces.length(); ++i) {
                    if (m_pieces[i]->id() == tmp->id()) {
                        m_pieces.remove(i);
                        qDebug() << "吃过路兵 - remove id: " << tmp->id() << "i: " << i;
                        qDebug() << "m_pieces.length(): " << m_pieces.length();

                        // 移除被吃的黑兵的图像
                        QModelIndex tmpIndex = createIndex(tmp->y() * 8 + tmp->x(), 0);
                        emit dataChanged(tmpIndex, tmpIndex);
                    }
                }
                prev.reset(new Pawn{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
                m_record.append(prev);
                qDebug() << "吃过路兵后---m_record.length(): " << m_record.length();
            }

        } else if (p->color() == Pieces::Black && toY == 5) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == toX && tmp->y() == toY - 1 && tmp->type() == Pieces::pawn
                    && tmp->color() == Pieces::White) {
                    isEmpty = false;
                    break; // 找到(toX, toY)的上方有白兵
                }
                tmp = nullptr;
            }
            if (!isEmpty) {
                // (toX, toY)的上方的白兵被移除
                for (int i = 0; i < m_pieces.length(); ++i) {
                    if (m_pieces[i]->id() == tmp->id()) {
                        m_pieces.remove(i);
                        qDebug() << "吃过路兵 - remove id: " << tmp->id();
                        qDebug() << "m_pieces.length(): " << m_pieces.length();

                        // 移除被吃的白兵的图像
                        QModelIndex tmpIndex = createIndex(tmp->y() * 8 + tmp->x(), 0);
                        emit dataChanged(tmpIndex, tmpIndex);
                    }
                }
                prev.reset(new Pawn{tmp->x(), tmp->y(), tmp->color(), tmp->id()});
                m_record.append(prev);
                qDebug() << "吃过路兵后---m_record.length(): " << m_record.length();
            }
        }
    }

    switch (p->type()) {
    case Pieces::pawn:
        prev.reset(new Pawn{p->x(), p->y(), p->color(), p->id()});
        break;
    case Pieces::bishop:
        prev.reset(new Bishop{p->x(), p->y(), p->color(), p->id()});
        break;
    case Pieces::knight:
        prev.reset(new Knight{p->x(), p->y(), p->color(), p->id()});
        break;
    case Pieces::rook:
        prev.reset(new Rook{p->x(), p->y(), p->color(), p->id()});
        break;
    case Pieces::queen:
        prev.reset(new Queen{p->x(), p->y(), p->color(), p->id()});
        break;
    case Pieces::king:
        prev.reset(new King{p->x(), p->y(), p->color(), p->id()});
        break;
    default:
        break;
    }

    m_record.append(prev);
    qDebug() << "m_record.length(): " << m_record.length();
    p->setX(toX);
    p->setY(toY);

    for (int i = 0; i < m_record.length(); ++i) {
        qDebug() << i << "m_record[i]->x(): " << m_record[i]->x()
                 << "    m_record[i]->y(): " << m_record[i]->y();
    }

    if (turn == WhitePlayer) {
        turn = BlackPlayer;
    } else if (turn == BlackPlayer) {
        turn = WhitePlayer;
    }

    // createIndex创建并返回一个 QModelIndex 对象，该对象指向模型中移动后的位置
    QModelIndex fromIndex = createIndex(fromY * 8 + fromX, 0);
    QModelIndex toIndex = createIndex(toY * 8 + toX, 0);

    // dataChanged是QAbstractItemModel的一个信号，通知界面更新棋子的位置
    // 两个参数都是newIndex，意味着只通知了一个数据项的改变，用于单个数据项的更新
    emit dataChanged(fromIndex, fromIndex);
    emit dataChanged(toIndex, toIndex);
}

QVector<int> Board::possibleMoves(int x, int y)
{
    QSharedPointer<Pieces> p;
    for (int i = 0; i < m_pieces.length(); ++i) {
        p = m_pieces[i];
        if (p->x() == x && p->y() == y) {
            break; // 找到当前棋子
        }
    }

    // 取消第一次移动
    QVector<QSharedPointer<Pieces>> pieces = initPieces();
    QSharedPointer<Pieces> piece;
    for (int i = 0; i < pieces.length(); ++i) {
        piece = pieces[i];
        if (p->x() == piece->x() && p->y() == piece->y() && p->color() == piece->color()
            && p->type() == piece->type() && p->id() == piece->id()) {
            // 和初始位置一样
            p->setFirstMove(true); // 设置第一次移动
        }
    }

    if (turn != colortoPlayer(p->color())) {
        return {};
    }

    switch (p->type()) {
    case Pieces::pawn: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 白子上移（y减少），黑子下移（y增加）
        int offset = p->color() == Pieces::Color::White ? -1 : 1;

        isEmpty = true;
        auto newPawn = new Pawn{p->x(), p->y() + 1 * offset, p->color(), p->id()};
        for (int i = 0; i < m_pieces.length(); ++i) {
            tmp = m_pieces[i];
            if (tmp->x() == newPawn->x() && tmp->y() == newPawn->y()) {
                isEmpty = false;
                break; // 找到棋子, 说明当前x,y位置不为空
            }
            tmp = nullptr;
        }
        // 没有棋子才可以前进
        if (isEmpty && newPawn->y() < 8 && newPawn->y() >= 0) {
            int pos = newPawn->y() * 8 + newPawn->x();
            if (newPawn->y() == 0 || newPawn->y() == 7) {
                moveList.append(pos); // 晋升(兵升变)
            } else {
                moveList.append(pos); // 移动
            }

            //第一次移动可以再 + 1 * offset
            isEmpty = true;
            newPawn->setY(newPawn->y() + 1 * offset);
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == newPawn->x() && tmp->y() == newPawn->y()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }
            pos = newPawn->y() * 8 + newPawn->x();
            if (p->isFirstMove() && isEmpty) {
                moveList.append(pos); // 移动
            }
        }

        // 吃子(斜着)
        // 右上/右下
        isEmpty = true;
        newPawn = new Pawn{p->x() + 1, p->y() + 1 * offset, p->color(), p->id()};
        for (int i = 0; i < m_pieces.length(); ++i) {
            tmp = m_pieces[i];
            if (tmp->x() == newPawn->x() && tmp->y() == newPawn->y()) {
                isEmpty = false;
                break; // 找到棋子, 说明当前x,y位置不为空
            }
            tmp = nullptr;
        }
        int pos = newPawn->y() * 8 + newPawn->x();
        if (newPawn->y() < 8 && newPawn->y() >= 0 && newPawn->x() < 8 && !isEmpty
            && tmp->color() != p->color()) {
            moveList.append(pos); // 吃子
        }

        // 左上/左下
        isEmpty = true;
        newPawn = new Pawn{p->x() - 1, p->y() + 1 * offset, p->color(), p->id()};
        for (int i = 0; i < m_pieces.length(); ++i) {
            tmp = m_pieces[i];
            if (tmp->x() == newPawn->x() && tmp->y() == newPawn->y()) {
                isEmpty = false;
                break; // 找到棋子, 说明当前x,y位置不为空
            }
            tmp = nullptr;
        }
        pos = newPawn->y() * 8 + newPawn->x();
        if (newPawn->y() < 8 && newPawn->y() >= 0 && newPawn->x() >= 0 && !isEmpty
            && tmp->color() != p->color()) {
            moveList.append(pos); // 吃子
        }

        // 吃过路兵
        // 白方兵y = 3, 黑方兵y = 4
        if ((p->y() == 3 && p->color() == Pieces::White)
            || (p->y() == 4 && p->color() == Pieces::Black)) {
            // 检查左方是否有敌方兵
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == p->x() - 1 && tmp->y() == p->y() && tmp->type() == Pieces::pawn
                    && tmp->color() != p->color()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }
            if (!isEmpty) {
                pos = (tmp->y() + 1 * offset) * 8 + tmp->x();
                moveList.append(pos);
            }

            // 检查右方是否有敌方兵
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == p->x() + 1 && tmp->y() == p->y() && tmp->type() == Pieces::pawn
                    && tmp->color() != p->color()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }
            if (!isEmpty) {
                pos = (tmp->y() + 1 * offset) * 8 + tmp->x();
                moveList.append(pos);
            }
        }

        return moveList;
    }
    case Pieces::bishop: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 左上
        for (int x = p->x() - 1, y = p->y() - 1; x >= 0 && y >= 0; x--, y--) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 右上
        for (int x = p->x() + 1, y = p->y() - 1; x < 8 && y >= 0; x++, y--) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到当前棋子, 说明当前x,y不为空, tmp != nullptr
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 右下
        for (int x = p->x() + 1, y = p->y() + 1; x < 8 && y < 8; x++, y++) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到当前棋子, 说明当前x,y不为空, tmp != nullptr
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 左下
        for (int x = p->x() - 1, y = p->y() + 1; x >= 0 && y < 8; x--, y++) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到当前棋子, 说明当前x,y不为空, tmp != nullptr
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        return moveList;
    }
    case Pieces::knight: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 马能走八个位置（两格拐一格）   变化量：{x, y}
        int offsets[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

        for (int i = 0; i < 8; i++) {
            int x = p->x() + offsets[i][0];
            int y = p->y() + offsets[i][1];

            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (isEmpty) {
                    moveList.append(pos); // 移动
                } else if (tmp->color() != p->color()) {
                    moveList.append(pos); // 吃子
                }
            }
        }

        return moveList;
    }
    case Pieces::rook: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 向上移动
        for (int i = p->y() - 1; i >= 0; i--) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == p->x() && tmp->y() == i) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = i * 8 + p->x();
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向下移动
        for (int i = p->y() + 1; i < 8; i++) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == p->x() && tmp->y() == i) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = i * 8 + p->x();
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向左移动
        for (int i = p->x() - 1; i >= 0; i--) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == i && tmp->y() == p->y()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = p->y() * 8 + i;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向右移动
        for (int i = p->x() + 1; i < 8; i++) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == i && tmp->y() == p->y()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = p->y() * 8 + i;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        return moveList;
    }
    case Pieces::queen: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 直着走，上下左右
        // 向上移动
        for (int i = p->y() - 1; i >= 0; i--) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == p->x() && tmp->y() == i) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = i * 8 + p->x();
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向下移动
        for (int i = p->y() + 1; i < 8; i++) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == p->x() && tmp->y() == i) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = i * 8 + p->x();
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向左移动
        for (int i = p->x() - 1; i >= 0; i--) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == i && tmp->y() == p->y()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = p->y() * 8 + i;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向右移动
        for (int i = p->x() + 1; i < 8; i++) {
            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == i && tmp->y() == p->y()) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = p->y() * 8 + i;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 斜着走，
        // 左上--、右上+-、右下++、左下-+

        // 向左上移动
        for (int x = p->x() - 1, y = p->y() - 1; x >= 0 && y >= 0; x--, y--) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向右上移动
        for (int x = p->x() + 1, y = p->y() - 1; x < 8 && y >= 0; x++, y--) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向左下移动
        for (int x = p->x() + 1, y = p->y() + 1; x < 8 && y < 8; x++, y++) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        // 向右下移动
        for (int x = p->x() - 1, y = p->y() + 1; x >= 0 && y < 8; x--, y++) {
            isEmpty = true;
            for (int i = 0; i < m_pieces.length(); ++i) {
                tmp = m_pieces[i];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }

            int pos = y * 8 + x;
            if (isEmpty) {
                moveList.append(pos); // 移动
            } else if (tmp->color() != p->color()) {
                moveList.append(pos); // 吃子
                break;
            } else {
                // isEmpty == false && tmp->color() == p->color()    同色
                break;
            }
        }

        return moveList;
    }
    case Pieces::king: {
        QVector<int> moveList;
        QSharedPointer<Pieces> tmp;
        bool isEmpty;

        // 王走八个位置（“米”字型，一次只能走一格）   变化量：{x, y}
        int offsets[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

        for (int i = 0; i < 8; i++) {
            int x = p->x() + offsets[i][0];
            int y = p->y() + offsets[i][1];

            isEmpty = true;
            for (int j = 0; j < m_pieces.length(); ++j) {
                tmp = m_pieces[j];
                if (tmp->x() == x && tmp->y() == y) {
                    isEmpty = false;
                    break; // 找到棋子, 说明当前x,y位置不为空
                }
                tmp = nullptr;
            }
            int pos = y * 8 + x;
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (isEmpty) {
                    moveList.append(pos); // 移动
                } else if (tmp->color() != p->color()) {
                    moveList.append(pos); // 吃子
                }
            }
        }

        // 王车易位
        // 四个车,1黑左上、2黑右上、3白左下、4白右下
        QSharedPointer<Pieces> rook1, rook2, rook3, rook4;
        qDebug() << "崩溃了。。。。。。。。。。。。。。。。。";

        for (int i = 0; i < m_pieces.length(); ++i) {
            rook1 = m_pieces[i];
            if (rook1->type() == Pieces::rook && rook1->x() == 0 && rook1->y() == 0
                && rook1->isFirstMove() && rook1->color() == Pieces::Black) {
                break; // 找到左上角的黑方车(未移动过)
            }
            rook1 = nullptr;
        }
        for (int i = 0; i < m_pieces.length(); ++i) {
            rook2 = m_pieces[i];
            if (rook2->type() == Pieces::rook && rook2->x() == 7 && rook2->y() == 0
                && rook2->isFirstMove() && rook2->color() == Pieces::Black) {
                break; // 找到右上角的黑方车(未移动过)
            }
            rook2 = nullptr;
        }
        for (int i = 0; i < m_pieces.length(); ++i) {
            rook3 = m_pieces[i];
            if (rook3->type() == Pieces::rook && rook3->x() == 0 && rook3->y() == 7
                && rook3->isFirstMove() && rook3->color() == Pieces::White) {
                break; // 找到左下角的白方车(未移动过)
            }
            rook3 = nullptr;
        }
        for (int i = 0; i < m_pieces.length(); ++i) {
            rook4 = m_pieces[i];
            if (rook4->type() == Pieces::rook && rook4->x() == 7 && rook4->y() == 7
                && rook4->isFirstMove() && rook4->color() == Pieces::White) {
                break; // 找到右下角的白方车(未移动过)
            }
            rook4 = nullptr;
        }

        // 王没有移动过
        if (p->type() == Pieces::king && p->isFirstMove()) {
            if (p->color() == Pieces::Black) {
                // 短易位(右)
                for (int i = 1; i <= 2; i++) {
                    isEmpty = true;
                    for (int j = 0; j < m_pieces.length(); ++j) {
                        tmp = m_pieces[j];
                        if (tmp->x() == p->x() + i && tmp->y() == p->y()) {
                            isEmpty = false;
                            break; // 找到王右边两格中有棋子，不为空
                        }
                        tmp = nullptr;
                    }
                    if (!isEmpty) {
                        break;
                    }
                }
                if (rook2 != nullptr && isEmpty) {
                    moveList.append(6);
                }

                // 长易位(左)
                for (int i = 1; i <= 3; i++) {
                    isEmpty = true;
                    for (int j = 0; j < m_pieces.length(); ++j) {
                        tmp = m_pieces[j];
                        if (tmp->x() == p->x() - i && tmp->y() == p->y()) {
                            isEmpty = false;
                            break; // 找到王左边三格中有棋子，不为空
                        }
                        tmp = nullptr;
                    }
                    if (!isEmpty) {
                        break;
                    }
                }
                if (rook1 != nullptr && isEmpty) {
                    moveList.append(2);
                }
            } else if (p->color() == Pieces::White) {
                // 短易位(右)
                for (int i = 1; i <= 2; i++) {
                    isEmpty = true;
                    for (int j = 0; j < m_pieces.length(); ++j) {
                        tmp = m_pieces[j];
                        if (tmp->x() == p->x() + i && tmp->y() == p->y()) {
                            isEmpty = false;
                            break; // 找到王右边两格中有棋子，不为空
                        }
                        tmp = nullptr;
                    }
                    if (!isEmpty) {
                        break;
                    }
                }
                if (rook4 != nullptr && isEmpty) {
                    moveList.append(62);
                }

                // 长易位(左)
                for (int i = 1; i <= 3; i++) {
                    isEmpty = true;
                    for (int j = 0; j < m_pieces.length(); ++j) {
                        tmp = m_pieces[j];
                        if (tmp->x() == p->x() - i && tmp->y() == p->y()) {
                            isEmpty = false;
                            break; // 找到王左边三格中有棋子，不为空
                        }
                        tmp = nullptr;
                    }
                    if (!isEmpty) {
                        break;
                    }
                }
                if (rook3 != nullptr && isEmpty) {
                    moveList.append(58);
                }
            }
        }

        return moveList;
    }
    default:
        return {};
    }
}

void Board::regretChess()
{
    QSharedPointer<Pieces> p, tmp;
    int i, j;

    if (m_record.length() < 1) {
        return;
    }

    for (i = 0; i < m_pieces.length(); ++i) {
        p = m_pieces[i];
        if (p->color() == m_record.last()->color() && p->id() == m_record.last()->id()) {
            // qDebug() << "m_record.last()->x():" << m_record.last()->x();
            // qDebug() << "m_record.last()->y():" << m_record.last()->y();
            // qDebug() << "p->x():" << p->x();
            // qDebug() << "p->y():" << p->y();
            // qDebug() << "悔棋---该棋子在m_pieces[i]里的索引为i: " << i << "id: " << p->id();
            break; // 找到当前棋子
        }
    }

    if (turn == WhitePlayer) {
        turn = BlackPlayer;
    } else if (turn == BlackPlayer) {
        turn = WhitePlayer;
    }

    // 普通走棋,恢复被吃的棋子
    if (m_record.length() > 2) {
        // m_record的倒数第二条记录
        tmp = m_record.at(m_record.length() - 2);

        // 倒数第二条记录的棋子位置，与最后一条记录的棋子走到的位置相同
        if (p->x() == tmp->x() && p->y() == tmp->y() && p->color() != tmp->color()) {
            m_pieces.append(tmp);

            QModelIndex beEaten = createIndex(tmp->y() * 8 + tmp->x(), 0);
            emit dataChanged(beEaten, beEaten);

            m_record.remove(m_record.length() - 2); // 移除倒数第二条记录
        }
    }

    // 吃过路兵,恢复被吃的棋子
    if (m_record.length() > 2) {
        // m_record的倒数第二条记录
        tmp = m_record.at(m_record.length() - 2);

        // 第二条记录记录的棋子位置，与最后一条记录的棋子走到的位置y相差1格
        if (p->type() == Pieces::pawn && tmp->type() == Pieces::pawn) {
            // 白子上移（y减少），黑子下移（y增加）
            int offset = p->color() == Pieces::Color::White ? -1 : 1;
            if (p->x() == tmp->x() && p->y() == tmp->y() + 1 * offset
                && p->color() != tmp->color()) {
                m_pieces.append(tmp);

                QModelIndex beEaten = createIndex(tmp->y() * 8 + tmp->x(), 0);
                emit dataChanged(beEaten, beEaten);

                m_record.remove(m_record.length() - 2); // 移除倒数第二条记录
            }
        }
    }

    // 王车易位,王水平移动了两格
    if (p->type() == Pieces::king && p->y() == m_record.last()->y()
        && (p->x() == m_record.last()->x() + 2 || p->x() == m_record.last()->x() - 2)) {
        qDebug() << "进入--------------------------------------";

        // m_record的倒数第二条记录,即车原来的位置
        tmp = m_record.at(m_record.length() - 2);
        QSharedPointer<Pieces> rook;
        for (int j = 0; j < m_pieces.length(); ++j) {
            rook = m_pieces[j];
            if (rook->type() == Pieces::rook && rook->color() == tmp->color()
                && rook->id() == tmp->id()) {
                break; // 找到车现在的位置
            }
        }

        // 车现在的位置
        int present = rook->y() * 8 + rook->x();

        rook->setX(tmp->x());
        rook->setY(tmp->y());

        QModelIndex fromIndex = createIndex(present, 0);
        QModelIndex toIndex = createIndex(tmp->y() * 8 + tmp->x(), 0);
        emit dataChanged(fromIndex, fromIndex);
        emit dataChanged(toIndex, toIndex);
        qDebug() << "车返回！！！";

        m_record.remove(m_record.length() - 2); // 移除倒数第二条记录
    }

    // 现在位置
    int index = p->y() * 8 + p->x();

    // 上一步棋位置
    p->setX(m_record.last()->x());
    p->setY(m_record.last()->y());

    // 兵升变,悔棋后恢复原来的类型
    if (p->type() != m_record.last()->type() && m_record.last()->type() == Pieces::pawn) {
        QSharedPointer<Pieces> newPawn{new Pawn{p->x(), p->y(), p->color(), p->id()}};

        m_pieces.append(newPawn);
        m_pieces[i].swap(m_pieces.last());
        m_pieces.pop_back();
        qDebug() << "change back to pawn";
    }

    QModelIndex now = createIndex(index, 0);
    QModelIndex prev = createIndex(p->y() * 8 + p->x(), 0);
    emit dataChanged(now, now);
    emit dataChanged(prev, prev);

    // qDebug() << "turn: " << turn;
    // qDebug() << "更新回退........";

    m_record.pop_back(); // 移除最后一条记录
    qDebug() << "悔棋---该棋子在m_pieces[i]里的索引为i: " << i << "id: " << p->id();
    qDebug() << "m_record.length(): " << m_record.length();
    qDebug() << "m_pieces.length(): " << m_pieces.length();
}
