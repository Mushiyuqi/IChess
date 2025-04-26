#pragma once

#include <QObject>
#include <QSharedPointer>

class Pieces : public QObject
{
    Q_OBJECT
public:
    enum Color { White, Black };
    enum PieceType {
        king,   // 王
        queen,  // 后
        rook,   // 车
        knight, // 马
        bishop, // 象
        pawn    // 兵
    };

    Pieces(int x, int y, const Color color, const int id);

    virtual ~Pieces();

    const int id();

    int x();

    void setX(int value);

    int y();

    void setY(int value);

    const Color color();

    virtual PieceType type() const = 0;

    bool isFirstMove();

    void setFirstMove(bool moved);

private:
    int m_x;
    int m_y;
    Color m_color;
    int m_id;
    bool firstMove = true;
};

// 兵
class Pawn : public Pieces
{
public:
    Pawn(int x, int y, const Color color, const int id);
    virtual ~Pawn();

    PieceType type() const override;
};

// 象
class Bishop : public Pieces
{
public:
    Bishop(int x, int y, const Color color, const int id);
    virtual ~Bishop();

    PieceType type() const override;
};

// 马
class Knight : public Pieces
{
public:
    Knight(int x, int y, const Color color, const int id);
    virtual ~Knight();

    PieceType type() const override;
};

// 车
class Rook : public Pieces
{
public:
    Rook(int x, int y, const Color color, const int id);
    virtual ~Rook();

    PieceType type() const override;
};

// 后
class Queen : public Pieces
{
public:
    Queen(int x, int y, const Color color, const int id);
    virtual ~Queen();

    PieceType type() const override;
};

// 王
class King : public Pieces
{
public:
    King(int x, int y, const Color color, const int id);
    virtual ~King();

    PieceType type() const override;
};
