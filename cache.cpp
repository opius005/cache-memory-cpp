#include <bits/stdc++.h>
#include <fstream>
using namespace std;
//#define Cache_Size 32 * 1024
//#define Block_Size 64
//#define Offset_Size 6
#define Ways 8
#define No_Of_Blocks 512
#define rw_bit_Size 4
#define No_Of_Sets 64
#define Address_Size 28
#define Set_No_Size 6
#define Tag_Size 12

vector<vector<pair<pair<bitset<1>, bitset<1>>, bitset<Tag_Size>>>> TAG_ARRAY(No_Of_Sets, vector<pair<pair<bitset<1>, bitset<1>>, bitset<Tag_Size>>>(Ways));

void place_tag(bitset<rw_bit_Size> rw_bit, bitset<Set_No_Size> set_no, bitset<Tag_Size> tag)
{
    if (TAG_ARRAY.at(set_no.to_ullong()).at(0).first.first == 1)
    {
        // write code to modify data in RAM
        TAG_ARRAY.at(set_no.to_ullong()).at(0).first.first == 0;
    }
    for (int i = 0; i < Ways - 1; i++)
    {
        TAG_ARRAY.at(set_no.to_ulong()).at(i) = TAG_ARRAY.at(set_no.to_ulong()).at(i + 1);
    }
    TAG_ARRAY.at(set_no.to_ulong()).at(Ways - 1).first.second = 1;
    TAG_ARRAY.at(set_no.to_ulong()).at(Ways - 1).second = tag;
    if (rw_bit == 2)
    {
        TAG_ARRAY.at(set_no.to_ullong()).at(Ways - 1).first.first = 1;
    }
}

void rearrange_tag(bitset<rw_bit_Size> rw_bit, bitset<Set_No_Size> set_no, bitset<Tag_Size> tag)
{
    pair<pair<bitset<1>, bitset<1>>, bitset<Tag_Size>> temp_tag;
    int temp;
    for (int i = 0; i < Ways; i++)
    {
        if (TAG_ARRAY.at(set_no.to_ulong()).at(i).second == tag)
            temp = i;
    }
    temp_tag = TAG_ARRAY.at(set_no.to_ulong()).at(temp);
    for (int i = temp; i < Ways - 1; i++)
    {
        TAG_ARRAY.at(set_no.to_ulong()).at(i) = TAG_ARRAY.at(set_no.to_ulong()).at(i + 1);
    }
    TAG_ARRAY.at(set_no.to_ulong()).at(Ways - 1) = temp_tag;
    if (rw_bit == 2)
    {
        TAG_ARRAY.at(set_no.to_ullong()).at(Ways - 1).first.first = 1;
    }
}

bool check(bitset<Set_No_Size> set_no, bitset<Tag_Size> tag)
{
    bool check_bit = false;
    for (int i = 0; i < Ways; i++)
    {
        if (TAG_ARRAY.at(set_no.to_ulong()).at(i).first.second == 1)
            if (TAG_ARRAY.at(set_no.to_ulong()).at(i).second == tag)
                check_bit = true;
    }
    return check_bit;
}

bitset<Tag_Size> get_tag(bitset<Address_Size> Address)
{
    string sgt = Address.to_string();
    sgt = sgt.substr(rw_bit_Size, Tag_Size);

    return bitset<Tag_Size>(sgt);
}

bitset<Set_No_Size> get_set_no(bitset<Address_Size> Address)
{
    string sgs = Address.to_string();
    sgs = sgs.substr(rw_bit_Size + Tag_Size, Set_No_Size);

    return bitset<Set_No_Size>(sgs);
}

bitset<rw_bit_Size> get_rw_bit(bitset<Address_Size> Address)
{
    string srwb = Address.to_string();
    srwb = srwb.substr(0, rw_bit_Size);

    return bitset<rw_bit_Size>(srwb);
}

/*bitset<Offset_Size> get_offset(bitset<Address_Size> Address)
{
    string sgo = Address.to_string();
    sgo = sgo.substr(rw_bitSize+Tag_Size + Set_No_Size, Offset_Size);

    return bitset<Offset_Size>(sgo);
}*/

int main()
{
    int rhit_count = 0;
    int whit_count = 0;
    int r_cases = 0;
    int w_cases = 0;
    double rhit_rate;
    double whit_rate;
    bitset<Tag_Size> tag;
    bitset<Set_No_Size> set_no;
    bitset<rw_bit_Size> rw_bit;
    // bitset<Offset_Size> offset;
    bool validbit_check;
    vector<bitset<Address_Size>> Address;

    string line;

    ifstream CI("Cache_Input.txt");
    if (CI.is_open())
    {
        while (getline(CI, line))
        {
            Address.push_back(bitset<Address_Size>(line));
        }
    }
    else
        cout << "Unable to open file";
    CI.close();

    for (int i = 0; i < Address.size(); i++)
    {
        rw_bit = get_rw_bit(Address[i]);
        tag = get_tag(Address[i]);
        set_no = get_set_no(Address[i]);
        // offset = get_offset(Address[i]);

        validbit_check = check(set_no, tag);
        if (rw_bit == 1)
        {
            r_cases++;
            if (validbit_check)
            {
                rhit_count++;
                rearrange_tag(rw_bit, set_no, tag);
            }
            else
                place_tag(rw_bit, set_no, tag);
        }
        if (rw_bit == 2)
        {
            w_cases++;
            if (validbit_check)
            {
                whit_count++;
                rearrange_tag(rw_bit, set_no, tag);
            }
            else
                place_tag(rw_bit, set_no, tag);
        }
    }
    rhit_rate = ((double)rhit_count / r_cases) * 100;
    cout << "Read hit rate =" << rhit_rate << endl;

    whit_rate = ((double)whit_count / w_cases) * 100;
    cout << "Write hit rate =" << whit_rate << endl;
    cout << "hit rate =" << (double)(rhit_count + whit_count) / Address.size() * 100;
}