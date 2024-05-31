#include <cstddef>
#include <algorithm>
#include <iostream>

#define BLOCK_SIZE  8


class Block{
public:
    Block* prev{};
    Block* next{};
    int data{};

    explicit Block(int value): data(value), next(nullptr), prev(nullptr) {}
private:
};

class BigInt{
public:
    size_t size;
    Block* blocks;

    BigInt(): size(0), blocks(nullptr) {}

    ~BigInt(){
        destroy_bigint();
    }

    void destroy_bigint() {
        Block* current = blocks;
        while (current!= nullptr) {
            Block* nextBlock = current->next;
            delete current;
            current = nextBlock;
        }
        blocks = nullptr;
        size = 0;
    }


    void addBlock(int value) {
        auto* newBlock = new Block(value);
        if (blocks == nullptr) {
            blocks = newBlock;
        } else {
            Block* last = blocks;
            while (last->next!= nullptr) {
                last = last->next;
            }
            last->next = newBlock;
            newBlock->prev = last;
        }
        size++;
    }

    void print() const {
        Block* current = blocks;
        while (current!= nullptr) {
            std::cout << current->data;
            current = current->next;
        }
        std::cout << std::endl;
    }

    void fromString(const std::string& str) {
        destroy_bigint(); // Очищаем текущие данные перед заполнением новыми
        size_t len = str.length();
        size_t numBlocks = len / BLOCK_SIZE;
        if (len % BLOCK_SIZE!= 0) {
            numBlocks++;
        }

        for (size_t i = 0; i < numBlocks; ++i) {
            int startIdx = i * BLOCK_SIZE;
            int endIdx = std::min(startIdx + BLOCK_SIZE, len);
            std::string blockStr = str.substr(startIdx, endIdx - startIdx);
            int blockValue = std::stoi(blockStr); // Преобразование подстроки в число
            addBlock(blockValue);
        }
    }


    static void sum(BigInt& res, const BigInt& a, const BigInt& b) {
        size_t len = std::max(a.size, b.size) + 1;
        res.destroy_bigint(); // Clear existing blocks
        res.size = len;
        res.blocks = nullptr;

        Block* curA = a.blocks;
        Block* curB = b.blocks;
        while (curA!= nullptr && curA->next!= nullptr) curA = curA->next;
        while (curB!= nullptr && curB->next!= nullptr) curB = curB->next;

        int results[len];
        int carry = 0;

        for (int i = len - 1; i >= 0; --i) {
            int valA = (curA!= nullptr)? curA->data : 0;
            int valB = (curB!= nullptr)? curB->data : 0;

            int sum = valA + valB + carry;
            carry = sum / 100000000;
            sum %= 100000000;

            results[i] = sum;

            if (curA!= nullptr) curA = curA->prev;
            if (curB!= nullptr) curB = curB->prev;
        }

        for (size_t i = 0; i < len; ++i) {
            res.addBlock(results[i]);
        }
    }
};

int main() {
    BigInt a, b, res;

    a.fromString("7412589632145698741258963214753698417525");
    b.fromString("1234567890512345678912345671234561234563");

    a.print();
    std::cout << "+" << std::endl;
    b.print();
    std::cout << "=============================" << std::endl;
    BigInt::sum(res, a, b);
    res.print();
    std::cout << "-----------------------------" << std::endl;

    return 0;
}