#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<long long>>;

// ---------- Utility ----------
int digits(long long x) {
    if (x == 0) return 1;
    int d = 0;
    if (x < 0) { d++; x = -x; }
    while (x) { d++; x /= 10; }
    return d;
}

void printMatrix(const Matrix& M, const string& title = "") {
    if (!title.empty()) cout << title << "\n";
    if (M.empty()) { cout << "(empty)\n"; return; }
    int n = (int)M.size(), m = (int)M[0].size();
    long long maxAbs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maxAbs = max(maxAbs, llabs(M[i][j]));
        }
    }
    int w = max(2, digits(maxAbs) + 1); // +1 for spacing / sign
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(w) << M[i][j];
        }
        cout << "\n";
    }
}

// ---------- I/O ----------
bool loadFromFile(const string& filename, int& N, Matrix& A, Matrix& B, string& err) {
    ifstream fin(filename);
    if (!fin) { err = "Unable to open file: " + filename; return false; }
    if (!(fin >> N) || N <= 0) { err = "First value must be a positive integer N."; return false; }
    A.assign(N, vector<long long>(N));
    B.assign(N, vector<long long>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(fin >> A[i][j])) { err = "Failed reading A at (" + to_string(i) + "," + to_string(j) + ")"; return false; }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(fin >> B[i][j])) { err = "Failed reading B at (" + to_string(i) + "," + to_string(j) + ")"; return false; }
        }
    }
    return true;
}

void saveSampleInput(const string& filename) {
    ofstream fout(filename);
    fout << "4\n";
    fout << "01 02 03 04\n";
    fout << "05 06 07 08\n";
    fout << "09 10 11 12\n";
    fout << "13 14 15 16\n";
    fout << "13 14 15 16\n";
    fout << "09 10 11 12\n";
    fout << "05 06 07 08\n";
    fout << "01 02 03 04\n";
}

// ---------- Operations ----------
Matrix add(const Matrix& A, const Matrix& B) {
    int n = (int)A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = (int)A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            long long aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}

long long mainDiagonalSum(const Matrix& M) {
    long long s = 0; int n = (int)M.size();
    for (int i = 0; i < n; ++i) s += M[i][i];
    return s;
}

long long secondaryDiagonalSum(const Matrix& M) {
    long long s = 0; int n = (int)M.size();
    for (int i = 0; i < n; ++i) s += M[i][n - 1 - i];
    return s;
}

bool swapRows(Matrix& M, int r1, int r2) {
    int n = (int)M.size();
    if (r1 < 0 || r2 < 0 || r1 >= n || r2 >= n) return false;
    swap(M[r1], M[r2]);
    return true;
}

bool swapCols(Matrix& M, int c1, int c2) {
    int n = (int)M.size();
    if (c1 < 0 || c2 < 0 || c1 >= n || c2 >= n) return false;
    for (int i = 0; i < n; ++i) swap(M[i][c1], M[i][c2]);
    return true;
}

bool updateCell(Matrix& M, int r, int c, long long v) {
    int n = (int)M.size();
    if (r < 0 || c < 0 || r >= n || c >= n) return false;
    M[r][c] = v;
    return true;
}

// ---------- Menu ----------
void showMenu() {
    cout << "\n---- Matrix Operations ----\n";
    cout << "1) Reload from file\n";
    cout << "2) Add A + B\n";
    cout << "3) Multiply A * B\n";
    cout << "4) Diagonal sums (choose matrix)\n";
    cout << "5) Swap rows (choose matrix)\n";
    cout << "6) Swap columns (choose matrix)\n";
    cout << "7) Update element (choose matrix)\n";
    cout << "8) Print matrices\n";
    cout << "0) Exit\n";
    cout << "Select: ";
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string defaultFile = "input.txt";
    // Save a sample input if none exists
    ifstream test(defaultFile);
    if (!test.good()) {
        saveSampleInput(defaultFile);
        cerr << "[Info] Created sample '" << defaultFile << "' in working directory.\n";
    }

    string filename;
    if (argc >= 2) filename = argv[1];
    else {
        cout << "Enter input filename (default: input.txt): ";
        getline(cin, filename);
        if (filename.empty()) filename = defaultFile;
    }

    int N = 0;
    Matrix A, B;
    string err;
    if (!loadFromFile(filename, N, A, B, err)) {
        cerr << "Error: " << err << "\n";
        return 1;
    }
    cout << "Loaded N = " << N << " from '" << filename << "'.\n";
    printMatrix(A, "Matrix A:");
    printMatrix(B, "Matrix B:");

    while (true) {
        showMenu();
        int choice;
        if (!(cin >> choice)) break;
        if (choice == 0) break;

        if (choice == 1) {
            cout << "Filename: ";
            cin >> filename;
            if (!loadFromFile(filename, N, A, B, err)) cout << "Error: " << err << "\n";
            else {
                cout << "Reloaded N = " << N << ".\n"; 
                printMatrix(A, "Matrix A:");
                printMatrix(B, "Matrix B:");
            }
        } else if (choice == 2) {
            Matrix C = add(A, B);
            printMatrix(C, "A + B:");
        } else if (choice == 3) {
            Matrix C = multiply(A, B);
            printMatrix(C, "A * B:");
        } else if (choice == 4) {
            int which; cout << "Which matrix? (1=A, 2=B): "; cin >> which;
            const Matrix* M = (which == 2 ? &B : &A);
            long long mainSum = mainDiagonalSum(*M);
            long long secSum  = secondaryDiagonalSum(*M);
            cout << "Main diagonal sum = " << mainSum << "\n";
            cout << "Secondary diagonal sum = " << secSum << "\n";
        } else if (choice == 5) {
            int which; cout << "Which matrix? (1=A, 2=B): "; cin >> which;
            Matrix& M = (which == 2 ? B : A);
            int r1, r2; cout << "Enter r1 r2 (0-indexed): "; cin >> r1 >> r2;
            if (swapRows(M, r1, r2)) printMatrix(M, "After swap rows:");
            else cout << "Invalid indices.\n";
        } else if (choice == 6) {
            int which; cout << "Which matrix? (1=A, 2=B): "; cin >> which;
            Matrix& M = (which == 2 ? B : A);
            int c1, c2; cout << "Enter c1 c2 (0-indexed): "; cin >> c1 >> c2;
            if (swapCols(M, c1, c2)) printMatrix(M, "After swap cols:");
            else cout << "Invalid indices.\n";
        } else if (choice == 7) {
            int which; cout << "Which matrix? (1=A, 2=B): "; cin >> which;
            Matrix& M = (which == 2 ? B : A);
            int r, c; long long v; 
            cout << "Enter r c value (0-indexed): "; cin >> r >> c >> v;
            if (updateCell(M, r, c, v)) printMatrix(M, "After update:");
            else cout << "Invalid indices.\n";
        } else if (choice == 8) {
            printMatrix(A, "Matrix A:");
            printMatrix(B, "Matrix B:");
        } else {
            cout << "Invalid choice.\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
