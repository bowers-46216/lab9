#include <stdio.h>

struct RecordType {
	struct RecordType* next;
	int		id;
	char	name;
	int		order; 
};

struct HashType {
	struct RecordType* head;
};

int hash(int x) {
    return x % 10;
}

void insertRecord(struct HashType* hashTable, struct RecordType* record) {
    int index = hash(record->id);
    struct RecordType* head = hashTable[index].head;

    record->next = head;
    hashTable[index].head = record;
}

void displayRecordsInHash(struct HashType* hashTable, int hashSize) {

    int i;

    for (i = 0; i < hashSize; ++i) {
        printf("Index %d -> ", i);
        struct RecordType* current = hashTable[i].head;
		
        while (current != NULL) {
            printf("%d %c %d -> ", current->id, current->name, current->order);
            current = current->next;
        }
		
        printf("NULL\n");
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {

	FILE* f = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (f) {
		fscanf(f, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);

		for (i = 0; i < dataSz; ++i) {

			pRecord = *ppData + i;
			fscanf(f, "%d ", &n);

			pRecord->id = n;
			fscanf(f, "%c ", &c);

			pRecord->name = c;
			fscanf(f, "%d ", &n);

			pRecord->order = n;
		}

		fclose(f);
	}

	return dataSz;
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct RecordType pData[], int dataSz) {
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i) {
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");

}

int main(void) {
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", (struct HashType*)pRecords);
	displayRecordsInHash(pRecords, recordSz);
	return 0;
}