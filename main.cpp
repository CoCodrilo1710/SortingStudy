#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

ifstream fin ("teste.in");





long long getMax(vector <long long>& arr, long long  n)
{
	long long mx = arr[0];
	for(auto i = arr.begin()+1; i!=arr.end(); i++)
		if (*i > mx)
			mx = *i;
	return mx;
}


/// Count Sort

void countSort_alone(vector <long long>& arr, long long n)
{

	vector <long long> output(n);
	int i;

    long long Mx=getMax(arr,n);


    vector <long long> count(Mx);


	for (i = 0; i < n; i++)
		count[arr[i]]++;


	for (i = 1; i <= Mx; i++)
		count[i] += count[i - 1];


	for (i = n - 1; i >= 0; i--)
    {
		output[count[arr[i]] - 1 ] = arr[i];
		count[arr[i]]--;
	}


	for (i = 0; i < n; i++)
		arr[i] = output[i];

    count.clear();
    output.clear();
}





/// radix sort

void countSort(vector <long long>& arr, long long n, long long exp= 1 , long long baza= 0)
{

	vector <long long> output(n);
	long long i;

    vector <long long> count(baza);


	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % baza]++;


	for (i = 1; i < baza; i++)
		count[i] += count[i - 1];


	for (i = n - 1; i >= 0; i--)
    {
		output[count[(arr[i] / exp) % baza] - 1] = arr[i];
		count[(arr[i] / exp) % baza]--;
	}


	for (i = 0; i < n; i++)
		arr[i] = output[i];

    count.clear();
    output.clear();
}


void radixsort(vector <long long >& arr, long long n, long long baza)
{

	long long m = getMax(arr, n);


	for (long long exp = 1; m / exp > 0; exp *= baza)
		countSort(arr, n, exp, baza);

}


/// merge sort


void merged(vector <long long> &arr, long long p, long long q, long long r) {


  long long n1 = q - p + 1;
  long long n2 = r - q;

  vector <long long> L(n1), M(n2);

  for (long long i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (long long j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];


  long long i, j, k;
  i = 0;
  j = 0;
  k = p;


  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }


  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}


void mergeSort(vector <long long> &arr, long long l, long long r) {

  if (l < r) {

    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);


    merged(arr, l, m, r);
  }

  if (r<=l) return;
}


/// shell sort


void shellSort(vector <long long> &arr, long long n) {
  for (long long interval = n / 2; interval > 0; interval /= 2) {
    for (long long i = interval; i < n; i += 1) {
      long long temp = arr[i];
      long long j;
      for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
        arr[j] = arr[j - interval];
      }
      arr[j] = temp;
    }
  }
}



/// Heap Sort

void heapify(vector <long long> &arr, long long n, long long i)
{
    long long largest = i;
    long long l = 2 * i + 1;
    long long r = 2 * i + 2;


    if (l < n && arr[l] > arr[largest])
        largest = l;


    if (r < n && arr[r] > arr[largest])
        largest = r;


    if (largest != i) {
        swap(arr[i], arr[largest]);

    heapify(arr, n, largest);
    }
}


void heapSort(vector <long long> &arr, long long n)
{

    for (long long i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (long long i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


void print(vector <long long>& arr, int n)
{
	for(auto  i = arr.begin(); i!=arr.end(); i++)
		cout << *i << " ";
}


void generate_vector(vector<long long> &v, long long maxim)
{
    random_device rd;
    mt19937_64 eng(rd());

    uniform_int_distribution<long long> random(0, maxim);

    for(auto i = v.begin(); i!=v.end(); i++){
        *i = random(eng);
    }
}


int verif(vector<long long> &v)
{
    for (auto i=v.begin()+1; i!=v.end();i++)
        if (*i < *(i-1) ) return 0;
    return 1;
}


        void gameover_v1()
        {

            long long n=0; /// aici am nr de elemente
            long long baza=0;  /// aici am baza
            long long maxim=0; /// aici am maximul
            long long nr=0,j;


            fin>>nr;

            for (j=0;j<nr;j++)
            {

                fin>>n;
                fin>>maxim;

                baza=10;

                cout<<"N = "<<n<<"   "<<"Max = "<<maxim<<endl;
                cout<<endl;

                vector<long long> arr(n);
                vector<long long> copie1(n);

                generate_vector(arr,maxim);

                copie1.assign(arr.begin(), arr.end() );


                using namespace std::chrono;


                /// radix cu baza 10

                auto start = high_resolution_clock::now();

                radixsort(arr, n, baza);


                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds> (stop - start);


                cout<<duration.count()<<" Radix Sort & Baza 10 "<<"    | status sortare: "<<verif(arr) <<endl;



                arr.assign(copie1.begin(), copie1.end() );



                /// cu baza 2^16


                baza=pow(2,16);


                auto start1 = high_resolution_clock::now();



                radixsort(arr, n, baza);



                auto stop1 = high_resolution_clock::now();

                auto duration1 = duration_cast<microseconds> (stop1 - start1);


                cout<<duration1.count()<<" Radix Sort & Base 2^16 "<<"    | status sortare: "<<verif(arr) <<endl;



                arr.assign(copie1.begin(), copie1.end() );




                /// cu baza 2^15


                baza=pow(2,15);


                auto start2 = high_resolution_clock::now();



                radixsort(arr, n, baza);



                auto stop2 = high_resolution_clock::now();

                auto duration2 = duration_cast<microseconds> (stop2 - start2);


                cout<<duration2.count()<<" Radix Sort & Base 2^15 "<<"    | status sortare: "<<verif(arr) <<endl;


                arr.assign(copie1.begin(), copie1.end() );



                /// merge sort

               auto start4 = high_resolution_clock::now();



                mergeSort(arr, 0, n-1);



                auto stop4 = high_resolution_clock::now();

                auto duration4 = duration_cast<microseconds> (stop4 - start4);


                cout<<duration4.count()<<" Merge Sort |  "<<"      | status sortare: "<<verif(arr) <<endl;




                arr.assign(copie1.begin(), copie1.end() );




                /// shell sort


                auto start5 = high_resolution_clock::now();



                shellSort(arr, n);



                auto stop5 = high_resolution_clock::now();

                auto duration5 = duration_cast<microseconds> (stop5 - start5);


                cout<<duration5.count()<<" Shell Sort | "<<"    | status sortare: "<<verif(arr) <<endl;

                 arr.assign(copie1.begin(), copie1.end() );





                /// STL Sort


               auto start6 = high_resolution_clock::now();



                sort(arr.begin(),arr.end());



                auto stop6 = high_resolution_clock::now();

                auto duration6 = duration_cast<microseconds> (stop6 - start6);


                cout<<duration6.count()<<" STL Sort (Intro Sort) |   "<<"    | status sortare: "<<verif(arr) <<endl;


                arr.assign(copie1.begin(), copie1.end() );


                /// Heap Sort

                 auto start7 = high_resolution_clock::now();



                heapSort(arr, n);



                auto stop7 = high_resolution_clock::now();

                auto duration7 = duration_cast<microseconds> (stop7 - start7);


                cout<<duration7.count()<<" Heap Sort |   "<<"    | status sortare: "<<verif(arr) <<endl;




                arr.assign(copie1.begin(), copie1.end() );




                /// Count Sort



        try
        {
                auto start8 = high_resolution_clock::now();
                countSort_alone(arr, n);
                auto stop8 = high_resolution_clock::now();

                auto duration8 = duration_cast<microseconds> (stop8 - start8);


                cout<<duration8.count()<<" Count Sort |   "<<"    | status sortare: "<<verif(arr) <<endl;

        }
        catch(const std::bad_alloc&)
        {
            cout<<endl;
            cout<<" Count Sort | NEREUSIT  "<<"    | status sortare: "<<verif(arr) <<endl;

        }




                cout<<endl;

                arr.clear();
                copie1.clear();



            }

        }


int gameover(int nrsortare, vector <long long> arr, long long maxim, long long n)
{

      ///  vector<long long> arr(n);
        vector<long long> copie1(n);

       /// generate_vector(arr,maxim);

        copie1.assign(arr.begin(), arr.end() );
        int baza;

    if (nrsortare==0)
    {
            using namespace std::chrono;

             baza=10;

            /// radix cu baza 10

            auto start = high_resolution_clock::now();

            radixsort(arr, n, baza);


            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds> (stop - start);


            return duration.count();

    }

    arr.assign(copie1.begin(), copie1.end() );

    if (nrsortare==1)
    {

            /// cu baza 2^16


            baza=pow(2,16);

            using namespace std::chrono;
            auto start1 = high_resolution_clock::now();



            radixsort(arr, n, baza);



            auto stop1 = high_resolution_clock::now();

            auto duration1 = duration_cast<microseconds> (stop1 - start1);


            return duration1.count();

    }


        arr.assign(copie1.begin(), copie1.end() );


    if (nrsortare==2)
    {
            /// cu baza 2^15


            baza=pow(2,15);

            using namespace std::chrono;
            auto start2 = high_resolution_clock::now();



            radixsort(arr, n, baza);



            auto stop2 = high_resolution_clock::now();

            auto duration2 = duration_cast<microseconds> (stop2 - start2);


            return duration2.count();

    }


        arr.assign(copie1.begin(), copie1.end() );


    if (nrsortare==3)
    {

            /// merge sort

            using namespace std::chrono;
           auto start4 = high_resolution_clock::now();



            mergeSort(arr, 0, n-1);



            auto stop4 = high_resolution_clock::now();

            auto duration4 = duration_cast<microseconds> (stop4 - start4);


            return duration4.count();

    }


        arr.assign(copie1.begin(), copie1.end() );


    if (nrsortare==4)
    {

            /// shell sort

            using namespace std::chrono;
            auto start5 = high_resolution_clock::now();



            shellSort(arr, n);



            auto stop5 = high_resolution_clock::now();

            auto duration5 = duration_cast<microseconds> (stop5 - start5);


            return duration5.count();

    }

         arr.assign(copie1.begin(), copie1.end() );


    if (nrsortare==5)
    {
            /// STL Sort

            using namespace std::chrono;
           auto start6 = high_resolution_clock::now();



            sort(arr.begin(),arr.end());



            auto stop6 = high_resolution_clock::now();

            auto duration6 = duration_cast<microseconds> (stop6 - start6);


            return duration6.count();

    }


        arr.assign(copie1.begin(), copie1.end() );

    if (nrsortare==6)

    {
            /// Heap Sort
                using namespace std::chrono;
             auto start7 = high_resolution_clock::now();



            heapSort(arr, n);



            auto stop7 = high_resolution_clock::now();

            auto duration7 = duration_cast<microseconds> (stop7 - start7);


            return duration7.count();

    }


        arr.assign(copie1.begin(), copie1.end() );


    if (nrsortare==7)

        {
        /// Count Sort
            using namespace std::chrono;
         auto start8 = high_resolution_clock::now();

try
    {

            countSort_alone(arr, n);
            auto stop8 = high_resolution_clock::now();

            auto duration8 = duration_cast<microseconds> (stop8 - start8);


            return duration8.count();

    }
    catch(const std::bad_alloc&)
    {
        return -100;
    }

    }

        arr.clear();
        copie1.clear();



        }


void generate_raport()
{
    ofstream rapo("raport1.csv");
    rapo<<",Radix Sort & Baza 10, Radix Sort & Base 2^16, Radix Sort & Base 2^15, Merge Sort, Shell Sort, STL Sort (Intro Sort), Heap Sort, Count Sort\n";

    for(long long n = 10000; n<=10000000; n+=10000){

        rapo<<n;
        vector<long long> arr(n);
        generate_vector(arr, 100000000000);

        for(int i=0;i<8;i++){
            rapo<<","<<gameover(i, arr, 100000000000, n);
        }

        rapo<<"\n";
    }

    rapo.close();
}

int main()
{

    generate_raport();



    return 0;


}
