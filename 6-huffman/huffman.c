#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// ���� �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ 
void init(HeapType* h) {
    h->heap_size = 0;
}

// �� ���� ��� �Լ�
void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// ���� ������ ����
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// �ּҰ� ����
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key) break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}

// �� ���� �ּ� ��带 ��ĥ ���� ���
void print_merge(int key1, int key2) {
    printf("///%d + %d -> %d\n", key1, key2, key1 + key2);
}

// ���� Ʈ�� ����
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// ���� Ʈ�� ����
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// ���� ��� ���� Ȯ��
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// �迭 ���
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// ������ �ڵ� ���
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// ������ Ʈ�� ����
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    HeapType* heap = create();
    init(heap);

    // ���� �� ���ڿ� �󵵸� �����ϰ� ���
    for (int i = 0; i < size; i++) {
        element e;
        e.key = frequencies[i];
        e.ptree = make_tree(NULL, NULL);
        e.ptree->ch = characters[i];
        insert_min_heap(heap, e);
        print_heap(heap); // �� ���� ���
    }

    // �� ���� ������ Ʈ���� �����ϰ� �ٽ� �����ϸ� ���
    for (int i = 1; i < size; i++) {
        element e1 = delete_min_heap(heap);
        element e2 = delete_min_heap(heap);

        print_merge(e1.key, e2.key); // ���յ� �� ���

        TreeNode* node = make_tree(e1.ptree, e2.ptree);
        element e;
        e.key = e1.key + e2.key;
        e.ptree = node;

        insert_min_heap(heap, e);
        print_heap(heap); // ���� �� �� ���� ���
    }

    element e = delete_min_heap(heap);
    TreeNode* root = e.ptree;
    free(heap);
    return root;
}

// ������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int arr[100], top = 0;
    print_codes(root, arr, top);
    destroy_tree(root);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
