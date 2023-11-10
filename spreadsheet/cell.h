#pragma once

#include "common.h"
#include "formula.h"

#include <functional>
#include <unordered_set>

class Sheet;

class Cell : public CellInterface {
public:
    Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

    // Возвращает список ячеек, которые непосредственно задействованы в вычислении
    // формулы. Список отсортирован по возрастанию и не содержит повторяющихся
    // ячеек.
    std::vector<Position> GetReferencedCells() const override;

    bool IsReferenced() const;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    bool WouldIntroduceCircularDependency(const Impl& new_impl) const;
    void InvalidateCacheRecursive(bool force = false);

    //значение ячейки
    std::unique_ptr<Impl> impl_;
    //ссылка на таблицу
    Sheet& sheet_;
    //зависимости
    std::unordered_set<Cell*> lhs_nodes_;
    std::unordered_set<Cell*> rhs_nodes_;
};
