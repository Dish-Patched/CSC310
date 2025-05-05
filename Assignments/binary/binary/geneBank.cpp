#include "geneBank.h"

// =================================== PUBLIC FUNCTIONS =======================================================

GENE_BANK::GENE_BANK() {
    this->fileSize = 0;
    this->entryByte = sizeof(Sample);
}

GENE_BANK::~GENE_BANK() {
    cout << "Destructing ..." << endl;
}

void GENE_BANK::sort(Sample array[], int fileSize) {
    if (fileSize != 0) {
        this->fileSize = fileSize;  
        this->p_timSort(array, fileSize);
    } else 
        throw MyException("ERROR: Empty file to sort!");
}

void GENE_BANK::indexSamples(Sample array[], int indexArray[]) {
    this->p_index(array, indexArray);
}

void GENE_BANK::displayResearcher(int speciesCode, int offset, char* filename) {
    bool checkSample;

    checkSample = searchSample(speciesCode, offset, filename);

    if (checkSample) {
        p_displayResearcher(speciesCode, offset, filename);
    } else {
        cout << "Sample record doesn't exist! Can't display researcher name." << endl;
    }
}

bool GENE_BANK::searchSample(int speciesCode, int offset, char* filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile.is_open()) {
        throw MyException("ERROR: Cannot open binary file for reading.");
    }

    // Calculate byte offset
    int recordPosition = offset * sizeof(Sample);
    inFile.seekg(recordPosition, ios::beg);

    Sample temp;
    inFile.read(reinterpret_cast<char*>(&temp), sizeof(Sample));

    // Check validity
    if (inFile && temp.speciesCode == speciesCode) {
        inFile.close();
        return true;
    }

    inFile.close();
    return false;
}

void GENE_BANK::updateResearcher(int speciesCode, int offset, char* newName, char* filename) {
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if (checkSample) {
        p_updateResearcher(speciesCode, offset, newName, filename);
    } else {
        cout << "Sample record to be updated doesn't exist!" << endl;
    }
}

void GENE_BANK::deleteSample(int speciesCode, int offset, char* filename) {
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if (checkSample) {
        p_deleteSample(speciesCode, offset, filename);
    } else {
        cout << "Sample record to be deleted doesn't exist!" << endl;
    }
}

void GENE_BANK::printSampleRange(int speciesCode, int startIndex, int endIndex, char* filename) {
    if (startIndex >= endIndex)
        throw MyException("ERROR: start index is larger than end index!");
    else
        this->p_printRange(speciesCode, startIndex, endIndex, filename);
}

// =================================== PRIVATE FUNCTIONS =======================================================

const int RUN = 32;

void GENE_BANK::p_timSort(Sample array[], int fileSize) {
    // Step 1: Sort individual subarrays using insertion sort
    for (int i = 0; i < fileSize; i += RUN) {
        p_insertionSort(array, i, min(i + RUN - 1, fileSize - 1));
    }

    // Step 2: Merge sorted runs
    for (int size = RUN; size < fileSize; size *= 2) {
        for (int left = 0; left < fileSize; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), fileSize - 1);

            if (mid < right)
                p_merge(array, left, mid, right);
        }
    }
}

void GENE_BANK::p_insertionSort(Sample array[], int beg, int end) {
    for (int i = beg + 1; i <= end; i++) {
        Sample temp = array[i];
        int j = i - 1;

        while (j >= beg && array[j].speciesCode > temp.speciesCode) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

void GENE_BANK::p_merge(Sample array[], int beg, int mid, int end) {
    int len1 = mid - beg + 1, len2 = end - mid;
    Sample* left = new Sample[len1];
    Sample* right = new Sample[len2];

    for (int i = 0; i < len1; i++)
        left[i] = array[beg + i];
    for (int i = 0; i < len2; i++)
        right[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = beg;

    while (i < len1 && j < len2) {
        if (left[i].speciesCode <= right[j].speciesCode) {
            array[k++] = left[i++];
        } else {
            array[k++] = right[j++];
        }
    }

    while (i < len1)
        array[k++] = left[i++];
    while (j < len2)
        array[k++] = right[j++];

    delete[] left;
    delete[] right;
}

void GENE_BANK::p_index(Sample array[], int indexArray[]) {
    // Initialize all indices to -1 (indicating species not found yet)
    for (int i = 0; i < 5; i++)
        indexArray[i] = -1;

    // Traverse the sorted array once and record the first occurrence of each speciesCode
    for (int i = 0; i < fileSize; i++) {
        int code = array[i].speciesCode;

        // Only store the first occurrence
        if (indexArray[code] == -1) {
            indexArray[code] = i;
        }
    }
}

void GENE_BANK::p_displayResearcher(int speciesCode, int offset, char* filename) {
    /* These are the 5 unique species codes
        0 - H_SAP
        1 - M_MUS
        2 - D_MEL
        3 - E_COL
        4 - A_THA
    */

    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        throw MyException("ERROR: Cannot open binary file for reading.");
    }

    // Calculate byte offset
    int byteOffset = offset * sizeof(Sample);
    inFile.seekg(byteOffset, ios::beg);

    Sample temp;
    inFile.read(reinterpret_cast<char*>(&temp), sizeof(Sample));

    if (!inFile) {
        inFile.close();
        throw MyException("ERROR: Failed to read record from file.");
    }

    if (temp.speciesCode != speciesCode) {
        inFile.close();
        cout << "Species code mismatch. Record may be corrupt or misindexed." << endl;
        return;
    }

    cout << "Researcher: " << temp.researcher << endl;
    inFile.close();
}

void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char* newName, char* filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        throw MyException("ERROR: Cannot open file for updating.");
    }

    int byteOffset = offset * sizeof(Sample);
    file.seekg(byteOffset, ios::beg);

    Sample temp;
    file.read(reinterpret_cast<char*>(&temp), sizeof(Sample));

    if (!file || temp.speciesCode != speciesCode) {
        file.close();
        cout << "ERROR: Cannot update — species code mismatch or failed to read record." << endl;
        return;
    }

    // Update researcher name safely
    strncpy(temp.researcher, newName, MAX_RESEARCHER_NAME - 1);
    temp.researcher[MAX_RESEARCHER_NAME - 1] = '\0'; // Ensure null-termination

    // Seek back to write
    file.seekp(byteOffset, ios::beg);
    file.write(reinterpret_cast<char*>(&temp), sizeof(Sample));

    if (!file) {
        file.close();
        throw MyException("ERROR: Failed to write updated sample to file.");
    }

    cout << "Researcher updated successfully." << endl;
    file.close();
}

void GENE_BANK::p_deleteSample(int speciesCode, int offset, char* filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        throw MyException("ERROR: Cannot open file for deletion.");
    }

    int byteOffset = offset * sizeof(Sample);
    file.seekg(byteOffset, ios::beg);

    Sample temp;
    file.read(reinterpret_cast<char*>(&temp), sizeof(Sample));

    if (!file || temp.speciesCode != speciesCode) {
        file.close();
        cout << "ERROR: Cannot delete — species code mismatch or read failed." << endl;
        return;
    }

    // Mark record as deleted
    temp.sampleID = -1;
    strncpy(temp.researcher, "DELETED", MAX_RESEARCHER_NAME);
    temp.researcher[MAX_RESEARCHER_NAME - 1] = '\0';

    // Seek back and overwrite
    file.seekp(byteOffset, ios::beg);
    file.write(reinterpret_cast<char*>(&temp), sizeof(Sample));

    if (!file) {
        file.close();
        throw MyException("ERROR: Failed to write deleted record.");
    }

    cout << "Sample deleted (marked) successfully." << endl;
    file.close();
}

void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw MyException("ERROR: Cannot open file for reading range.");
    }

    Sample temp;
    for (int i = startIndex; i < endIndex; ++i) {
        file.seekg(i * sizeof(Sample), ios::beg);
        file.read(reinterpret_cast<char*>(&temp), sizeof(Sample));

        if (!file) {
            cout << "Failed to read record at index " << i << endl;
            continue;
        }

        if (temp.sampleID != -1 && temp.speciesCode == speciesCode) {
            cout << "SampleID: " << temp.sampleID
                 << ", SpeciesCode: " << temp.speciesCode
                 << ", Purity: " << temp.purityScore
                 << ", Researcher: " << temp.researcher << endl;
        }
    }

    file.close();
}
