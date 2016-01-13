#include <iostream>

#include <cstring>

class SmallAllocator {
    struct Descriptor {
        unsigned int size = 0;
        char *next = nullptr;
    };

private:
    static const unsigned int BLOCK_SIZE = sizeof(long double);
    static const unsigned int RESERVED_BLOCKS = 131072;
    static const unsigned int RESERVED_SIZE = RESERVED_BLOCKS * BLOCK_SIZE;
    static const unsigned int DESCRIPTOR_BLOCKS = (sizeof(Descriptor) + BLOCK_SIZE - 1) / BLOCK_SIZE;
    static const unsigned int DESCRIPTOR_SIZE = DESCRIPTOR_BLOCKS * BLOCK_SIZE;

    char Memory[RESERVED_SIZE];
    char *top;

    unsigned int blocks_count(unsigned int size) {
        return (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    }

    unsigned int aligned_size(unsigned int size) {
        return blocks_count(size) * BLOCK_SIZE;
    }

public:
    SmallAllocator() : top(Memory) { }

    void *Alloc(unsigned int Size) {
        unsigned int required_memory = DESCRIPTOR_SIZE + aligned_size(Size);
        char *new_top = top + required_memory;

        if (new_top > Memory + RESERVED_SIZE) {
            // TODO: find best place
            return nullptr;
        }

        char *storage = top + DESCRIPTOR_SIZE;
        Descriptor *descriptor = (Descriptor *) top;
        descriptor->size = Size;
        descriptor->next = new_top;
        top = new_top;

        return storage;
    };

    void *ReAlloc(void *Pointer, unsigned int Size) {
        if (Pointer < Memory + DESCRIPTOR_SIZE || Pointer == nullptr) {
            return nullptr;
        }

        Descriptor *descriptor = (Descriptor *) (Pointer - DESCRIPTOR_SIZE);
        unsigned int reserved_blocks = (descriptor->next - (char *) Pointer) / BLOCK_SIZE;
        unsigned int required_blocks = blocks_count(Size);

        if (required_blocks <= reserved_blocks) {
            descriptor->size = Size;
            return Pointer;
        }

        void *new_pointer = Alloc(Size);

        if (new_pointer == nullptr) {
            return nullptr;
        }

        std::memcpy(new_pointer, Pointer, descriptor->size);
        Free(Pointer);

        return new_pointer;
    };

    void Free(void *Pointer) {
        // TODO: clean memory
    };
};

int main() {
    SmallAllocator A1;
    int *A1_P1 = (int *) A1.Alloc(sizeof(int));
    A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));

    A1.Free(A1_P1);

    SmallAllocator A2;
    int *A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
    for (unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
    for (unsigned int i = 0; i < 10; i++) if (A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;

    int *A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
    for (unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
    for (unsigned int i = 0; i < 10; i++) if (A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
    for (unsigned int i = 0; i < 10; i++) if (A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;

    A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
    for (unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
    for (unsigned int i = 0; i < 20; i++) if (A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
    for (unsigned int i = 0; i < 10; i++) if (A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;

    A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
    for (unsigned int i = 0; i < 5; i++) if (A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
    for (unsigned int i = 0; i < 10; i++) if (A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;

    A2.Free(A2_P1);
    A2.Free(A2_P2);

    return 0;
}