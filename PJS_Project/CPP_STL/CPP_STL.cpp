// CPP_STL.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>       // 함수 객체

int Gen()
{
    static int iCount = 0;
    return iCount++;
}

int main()
{
    std::vector<int> list;

    list.push_back(5);
    for (int i = 0; i < 5; i++)
    {
        list.push_back(i);          // 뒤에서부터 
    }
    for (int i = 0; i < 5; i++)
    {
        list.insert(list.begin(), i);   // 맨앞에 삽입
    }
    for (int i = 0; i < 5; i++)
    {
        list.insert(list.end(), i);     // 맨뒤에 삽입
    }
    std::sort(list.begin(), list.end());   // <algorithm> 사용한 sort

    std::vector<int>::iterator iter = std::find(list.begin(), list.end(), 4);       // vector의 iterator 를 사용해 리스트의 시작부터 끝까지
                                                                              // 순회한다. vector에는 찾기기능이 없다.
    list.erase(iter);                   // 찾은 데이터 삭제
    int iValue = list.front();          // 맨앞 데이터
    int iValue2 = list.back();           // 맨뒤 데이터
    list.pop_back();                    // 맨뒤 제거 , 맨앞은 재할당을 해야하기 때문에 없다.

    for (std::vector<int>::iterator iter = list.begin();            // 리스트의 처음부터 끝일때까지 순환한다.
        iter != list.end();                                      // iterator는 배열인덱스로 접근할수 있다.
        iter++)
    {
        std::cout << " " << *iter;
    }
    std::cout << " " << std::endl;
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << " " << list[i];
    }
    std::cout << " " << std::endl;
    for (int iValue3 : list)                                      // list 값을 복사해 iValue에 할당
    {
        iValue3 = 100;
        std::cout << " " << iValue3;
    }
    for (int& iValue : list)                                    // iValue가 list를 참조하기 때문에 iValue의 값을 변경하면 list안 데이터가 바뀐다.
    {
        iValue = 10;
    }
    // std::copy        특정구간의 벡터를 카피해서 다른 객체 벡터에 할당한다. 할당할때에는 inserter 함수 사용
    std::vector<int> copyInt;
    std::copy(list.begin(), list.end(), std::back_inserter(copyInt));

    //generate
    // 특정범위의 원소를 함수의 반환값으로 체운다.(덮어씌운다)
    // 카운트할때 사용가능
    int (*pf)();
    pf = Gen;
    std::generate(list.begin(), list.end(), Gen);           // 마지막 인자에는 덮어씌울 함수 포인터 할당

    // std::transform
    // 특정범위의 원소를 변환한다.
    // 특정구간을 지정한 함수의 결과에 맞게 반환해 다른 객체 벡터에 할당한다.
    std::vector<int> vectorTrans;
    // <functional> 함수 객체 사용        [ std::함수객체<T>{} ]
    //[](int i) -> int { return i + 10; });     
    // 람다식으로도 사용가능
    std::transform(list.begin(), list.end(), std::back_inserter(vectorTrans), [](int i) -> int { return i + 10; });
    //std::transform(list.begin(), list.end(), copyInt.begin(), std::back_inserter(vectorTrans), std::multiplies<int>{});

    // std::merge
    // 병합 각 객체를 합쳐서 insertback 한다.
    // 정렬이 기본이다.
    std::vector<int> mergeVector;
    std::merge(list.begin(), list.end(),
        vectorTrans.begin(), vectorTrans.end(),
        std::back_inserter(mergeVector));

    std::vector<int> ret;
    ret.assign(mergeVector.begin(), mergeVector.end());             // 다른객체의 범위를 할당하거나 다른객체 원소의 n개 복사본을 할당한다.
    for (int i = 0; i < ret.size(); i++)
    {
        int jValue = ret.at(i);
        std::cout << " " << ret[i] << jValue;
    }

    list.clear();
    copyInt.clear();
    ret.clear();
    mergeVector.clear();
    vectorTrans.clear();

    return 0;
}

