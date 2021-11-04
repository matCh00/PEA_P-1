#include "Tests.h"



long long int read_QPC() {

    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
}



void Tests::startTests() {

    Graph *graph = new Graph();
    BruteForce *bf = new BruteForce();
    BranchAndBound *bb = new BranchAndBound();
    DynamicProgramming *dp = new DynamicProgramming();
    int instanceSize;
    int* path;
    int reps;
    int alg;
    int key = 1;
    long long int frequency, start, elapsed;
    long long int sum = 0;


    ofstream file;
    file.open("C:/Users/matic/Desktop/current projects/PEA_P-1/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }



    cout << "podaj liczbe miast:  ,  podaj liczbe powtorzen:  ,  wybierz: [1] - BF,  [2] - B&B,  [3] - DP";
    cin >> instanceSize; cin >> reps; cin >> alg;


    while (key == 1) {


        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);
            path = new int[instanceSize + 1];


            if (alg == 1) {

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                bf->algorithmBruteForce(graph->getMatrix(), path);

                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

                file << "BB: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            }


            if (alg == 2) {

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                bb->algorithmBranchAndBound(graph->getMatrix(), path);

                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

                file << "B&B: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            }


            if (alg == 3) {

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                dp->algorithmDynamicProgramming(graph->getMatrix(), path);

                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

                file << "DP: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            }

            sum = 0;
        }


        cout << "[x] - wyjscie,  [1] - dalej"; cin >> key;
        if (key == 1) {

            cout << "podaj liczbe miast:  ,  podaj liczbe powtorzen:  ,  wybierz: [1] - BF,  [2] - B&B,  [3] - DP";
            cin >> instanceSize; cin >> reps; cin >> alg;
        }
    }


    file.close();
}



void Tests::startAutomaticTests() {

    Graph *graph;
    BruteForce *bf;
    BranchAndBound *bb;
    DynamicProgramming *dp;
    int* path;
    long long int frequency, start, elapsed;
    long long int sum = 0;


    ofstream file;
    file.open("C:/Users/matic/Desktop/current projects/PEA_P-1/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }


    int reps = 30;
    int instanceSize = 17;


    for (int i = 0; i < 1; ++i) {

        instanceSize += 1;


        if (instanceSize < 13) {

            for (int i = 0; i < reps; ++i) {

                graph = new Graph(instanceSize);

                // BF

                bf = new BruteForce();
                path = new int[instanceSize + 1];

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                bf->algorithmBruteForce(graph->getMatrix(), path);

                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

            }
            file << "BF: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            sum = 0;
        }



        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);

            // BB

            bb = new BranchAndBound();
            path = new int[instanceSize + 1];

            QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
            start = read_QPC();

            bb->algorithmBranchAndBound(graph->getMatrix(), path);

            elapsed = read_QPC() - start;
            sum += (1000000.0 * elapsed) / frequency;
        }
        file << "B&B: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
        sum = 0;



        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);

            // DP

            dp = new DynamicProgramming();
            path = new int[instanceSize + 1];

            QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
            start = read_QPC();

            dp->algorithmDynamicProgramming(graph->getMatrix(), path);

            elapsed = read_QPC() - start;
            sum += (1000000.0 * elapsed) / frequency;
        }
        file << "DP: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
        sum = 0;
    }


    file.close();
}