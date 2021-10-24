/***************************************************************************//**
  @file     validation.c
  @brief    Validation function for uint16_t ID's
  @author   Matias Tripoli - Tobias Demeco
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "validation.h"
#include "array_compare.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static uint16_t nOfUsers = 0;
static User database[MAX_USERS];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Function that gets card ID from card reader */
int validateId(uint8_t enteredId[8])
{
    for(int i = 0; i < nOfUsers; i++)
    {
        if(compareArrays(database[i].id, enteredId, 8))
            return i;
    }
    return INVALID_ID;
}

bool validatePin(int userIndex, uint8_t enteredPin[4])
{
    if(compareArrays(database[userIndex].pin, enteredPin, 4))
        return true;
    else
        return false;
}

bool validateAdmin(int userIndex)
{
    if(database[userIndex].admin)
        return true;
    else
        return false;
}

void blockUser(int userIndex)
{
    database[userIndex].blocked = true;
}
void unblockUser(int userIndex)
{
    database[userIndex].blocked = false;
}

bool isUserBlocked(int userIndex)
{
    return database[userIndex].blocked;
}

/* Function that adds new user to system database */
bool addNewId(User newUser)
{
    if(nOfUsers == MAX_USERS)
    {
        //printf("The database is full");
        return false;
    }
    else
    {
        database[nOfUsers] = newUser;
        nOfUsers++;
        return true;
    }
}

void deleteUser(int userIndex)
{
    for(int i = userIndex; i < nOfUsers; i++)
    {
        database[i].admin = database[i+1].admin;
        for(int j = 0; j < 8; j++)
        {
            database[i].id[j] = database[i+1].id[j];
        }
        for(int j = 0; j < 4; j++)
        {
            database[i].pin[j] = database[i+1].pin[j];
        }
    }
    nOfUsers--;
}

void modifyPin(int userIndex, uint8_t newPin[4])
{
    for (int i = 0; i < 4; i++)
    {
        database[userIndex].pin[i] = newPin[i];
    }
}

bool checkIfAdmin(int user_index)
{
    return database[user_index].admin;
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
