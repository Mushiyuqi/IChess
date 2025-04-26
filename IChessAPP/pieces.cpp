#include "pieces.h"

Pieces::Pieces(int x, int y, Color color, int id)
    : m_x(x)
    , m_y(y)
    , m_color(color)
    , m_id(id)
    , firstMove(true)
{}

Pieces::~Pieces() {}

//返回棋子的索引
const int Pieces::id()
{
    return m_id;
}

//返回棋子的x坐标
int Pieces::x()
{
    return m_x;
}
//设置棋子的x坐标
void Pieces::setX(int value)
{
    m_x = value;
}
//返回棋子的y坐标
int Pieces::y()
{
    return m_y;
}
//设置棋子的y坐标
void Pieces::setY(int value)
{
    m_y = value;
}
//返回棋子的颜色
const Pieces::Color Pieces::color()
{
    return m_color;
}

bool Pieces::isFirstMove()
{
    return firstMove;
}

void Pieces::setFirstMove(bool moved)
{
    firstMove = moved;
}

Pawn::Pawn(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

Pawn::~Pawn() {}

Pawn::PieceType Pawn::type() const
{
    return pawn;
}

Bishop::Bishop(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

Bishop::~Bishop() {}

Bishop::PieceType Bishop::type() const
{
    return bishop;
}

Knight::Knight(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

Knight::~Knight() {}

Knight::PieceType Knight::type() const
{
    return knight;
}

Rook::Rook(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

Rook::~Rook() {}

Rook::PieceType Rook::type() const
{
    return rook;
}

Queen::Queen(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

Queen::~Queen() {}

Queen::PieceType Queen::type() const
{
    return queen;
}

King::King(int x, int y, const Color color, const int id)
    : Pieces(x, y, color, id)
{}

King::~King() {}

King::PieceType King::type() const
{
    return king;
}
