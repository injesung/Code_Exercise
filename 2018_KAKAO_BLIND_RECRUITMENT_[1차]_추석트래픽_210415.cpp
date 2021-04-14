#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <string.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>

using namespace std;
struct line_split
{
    double start_time;
    double end_time;
};
line_split struct_changer(string input)
{
    line_split res;
    string date, time, process_s;
    date = strtok((char*)input.c_str(), " ");
    time = strtok(NULL, " ");
    process_s = strtok(NULL, " ");
    //스트링 3개로 분할완료
    string hour_s, minute_s, sec_s, ms_s;
    double hour, minute, sec;
    double ms, process_time;
    hour_s = strtok((char*)time.c_str(), ":");
    minute_s = strtok(NULL, ":");
    sec_s = strtok(NULL, ".");
    ms_s = strtok(NULL, "");
    //시분초밀리초 스트링분할
    hour = atof(hour_s.c_str());
    minute = atof(minute_s.c_str());
    sec = atof(sec_s.c_str());
    ms = atof(ms_s.c_str());
    ms = ms / 1000;
    //시분초밀리초 숫자변환
    process_time = atof(strtok((char*)process_s.c_str(), "s"));
    if (process_time < 0.001 || process_time>3.000)
    {
        res.start_time = -9999;
        res.end_time = -9999;
        return res;
    }
    // cout << hour << " " << minute << " " << sec << " " << ms << " " << process_time << endl;//debug cout

    res.end_time = 3600 * hour + 60 * minute + sec + ms;
    res.start_time = 3600 * hour + 60 * minute + sec + ms - process_time + 0.001;
    //cout << "start : " << (double)res.start_time << " end : " << (double)res.end_time << endl;
    //printf("start : %f end : %f\n", res.start_time, res.end_time);
    return res;

}
bool comp(line_split a, line_split b)
{
    return a.start_time < b.start_time;
}
int solution(vector<string> lines) {
    int answer1 = 0;
    int answer2 = 0;
    vector<line_split> line_struct;
    for (int i = 0; i < lines.size(); i++)
    {
        line_struct.push_back(struct_changer(lines[i]));
    }
    double std_start = 0, std_end = 1;

    //끝시간 기준으로 확인하기
    for (int i = 0; i < line_struct.size(); i++)
    {
        int cnt = 0;
        std_start = line_struct[i].end_time;
        std_end = std_start + 0.9999;
        for (int j = 0; j < line_struct.size(); j++)
        {
            if (line_struct[j].start_time < std_start && line_struct[j].end_time < std_start)
                continue;
            if (line_struct[j].start_time <= std_start && line_struct[j].end_time >= std_start)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time <= std_start && line_struct[j].end_time >= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time >= std_start && line_struct[j].end_time <= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time >= std_start && line_struct[j].start_time <= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time > std_start)
                break;
        }
        if (answer1 < cnt)
            answer1 = cnt;
    }


    //시작시간 기준으로 sort하여 확인하기
    sort(line_struct.begin(), line_struct.end(), comp);

    for (int i = 0; i < line_struct.size(); i++)
    {
        int cnt = 0;
        std_start = line_struct[i].start_time;
        std_end = std_start + 0.9999;
        for (int j = 0; j < line_struct.size(); j++)
        {
            if (line_struct[j].start_time < std_start && line_struct[j].end_time < std_start)
                continue;
            if (line_struct[j].start_time <= std_start && line_struct[j].end_time >= std_start)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time <= std_start && line_struct[j].end_time >= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time >= std_start && line_struct[j].end_time <= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time >= std_start && line_struct[j].start_time <= std_end)
            {
                cnt++;
                continue;
            }
            if (line_struct[j].start_time > std_start)
                break;
        }
        if (answer2 < cnt)
            answer2 = cnt;
    }
    //cout<<"max : "<<max<<endl;*/
    if (answer1 > answer2)
        return answer1;
    else
        return answer2;
}
int main()
{
    string input1 = "2016-09-15 01:00:04.001 2.0s";
    string input2 = "2016-09-15 01:00:07.000 2s";
    vector<string> input;
    input.push_back(input1);
    input.push_back(input2);

    cout<<solution(input);

}