#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <unordered_map>


struct PositionHasher
{
    std::size_t operator()(const Position& pos) const
    {
        std::size_t xHash = std::hash<int>{}(pos.row);
        std::size_t yHash = std::hash<int>{}(pos.col);
        return xHash ^ (yHash << 1);
    }
};
//«Электронная таблица» наследует интерфейс SheetInterface
class Sheet : public SheetInterface {
public:

    using Table = std::unordered_map<Position, std::unique_ptr<Cell>, PositionHasher>;

    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    const Cell* GetCellPtr(Position pos) const;
    Cell* GetCellPtr(Position pos);

private:
	Table cells_;
};
