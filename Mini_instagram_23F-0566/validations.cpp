#include "validations.h"
bool validateusername(string username)
{
    bool is_valid = false;
    int strlength = username.length();
    for (int i = 0; i < strlength; i++)
    {
        if ((username[i] >= 'a' && username[i] <= 'z') || (username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= '0' && username[i] <= '9' || username[i] == '_'))
        {
            is_valid = true;
        }
        else
        {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool validate_strong_password(string password)
{
    bool is_valid = false;
    int strlength = password.length();
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    for (int i = 0; i < strlength; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            has_upper = true;
        }
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            has_lower = true;
        }
        if (password[i] >= '0' && password[i] <= '9')
        {
            has_digit = true;
        }
        if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126))
        {
            has_special = true;
        }
    }
    if (has_upper && has_lower && has_digit && has_special && strlength >= 8)
    {
        is_valid = true;
    }
    return is_valid;
}
bool validate_email(string email)
{
    bool is_valid = false;
    int strlength = email.length();
    bool has_at = false;
    bool has_dot = false;
    for (int i = 0; i < strlength; i++)
    {
        if (email[i] == '@')
        {
            has_at = true;
        }
        if (email[i] == '.')
        {
            has_dot = true;
        }
    }
    if (has_at && has_dot)
    {
        is_valid = true;
    }
    return is_valid;
}

bool validate_DOB(string dob)
{
    bool is_valid = false;
    int strlength = dob.length();
    if (strlength == 10)
    {
        if (dob[2] == '-' && dob[5] == '-')
        {
            if (dob[0] >= '0' && dob[0] <= '3' && dob[1] >= '0' && dob[1] <= '9' && dob[3] >= '0' && dob[3] <= '1' && dob[4] >= '0' && dob[4] <= '9' && dob[6] >= '0' && dob[6] <= '9' && dob[7] >= '0' && dob[7] <= '9' && dob[8] >= '0' && dob[8] <= '9' && dob[9] >= '0' && dob[9] <= '9')
            {
                is_valid = true;
            }
        }
    }
    return is_valid;
}
