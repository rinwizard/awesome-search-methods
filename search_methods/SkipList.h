#pragma once

#include <vector>
#include <cstddef>
#include <random>
#include <memory>
#include <utility>

class SkipList {
private:
    int maxlevel = 16;

    struct Node {
        int value;
        std::size_t index;
        std::vector<Node*> next;

        Node(int value, std::size_t index, int level)
            : value(value),
            index(index),
            next(level + 1, nullptr)
        {
        }
    };

    Node head;
    std::vector<std::unique_ptr<Node>> nodes;
    std::mt19937 generator;
    std::uniform_int_distribution<int> coin;

    int randomLevel()
    {
        int level = 0;

        while (level < maxlevel - 1 && coin(generator) == 1)
        {
            ++level;
        }

        return level;
    }

public:
    SkipList()
        : head(0, 0, maxlevel - 1),
        generator(std::random_device{}()),
        coin(0, 1)
    {
    }

    void insert(int value, std::size_t index)
    {
        Node* current = &head;
        std::vector<Node*> update(maxlevel, nullptr);

        for (int i = maxlevel - 1; i >= 0; --i)
        {
            while (current->next[i] != nullptr &&
                current->next[i]->value < value)
            {
                current = current->next[i];
            }

            update[i] = current;
        }

        int level = randomLevel();

        auto newNode = std::make_unique<Node>(value, index, level);
        Node* newNodePtr = newNode.get();

        nodes.push_back(std::move(newNode));

        for (int i = 0; i <= level; ++i)
        {
            newNodePtr->next[i] = update[i]->next[i];
            update[i]->next[i] = newNodePtr;
        }
    }

    std::size_t search(int target)
    {
        Node* current = &head;

        for (int i = maxlevel - 1; i >= 0; --i)
        {
            while (current->next[i] != nullptr &&
                current->next[i]->value < target)
            {
                current = current->next[i];
            }
        }

        current = current->next[0];

        if (current != nullptr && current->value == target)
        {
            return current->index;
        }

        return static_cast<std::size_t>(-1);
    }
};

inline std::size_t skip_list_search(
    const std::vector<int>& data,
    const int& target)
{
    SkipList list;

    for (std::size_t i = 0; i < data.size(); ++i)
    {
        list.insert(data[i], i);
    }

    return list.search(target);
}
