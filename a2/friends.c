#include "friends.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int check_friend_helper(User* first, User* second);
void update_friend_helper(User *delete, User *temp);


/*
 * Create a new user with the given name.  Insert it at the tail of the list
 * of users whose head is pointed to by *user_ptr_add.
 *
 * Return:
 *   - 0 if successful
 *   - 1 if a user by this name already exists in this list
 *   - 2 if the given name cannot fit in the 'name' array
 *       (don't forget about the null terminator)
 */
int create_user(const char *name, User **user_ptr_add) {
    //return 2 - not qualified
    if(name == NULL||strlen(name) >= MAX_NAME){
        return 2;
    }

    //initialize new user
    User *new_user = malloc(sizeof(User));
    new_user->next = NULL;
    strcpy(new_user->name, name);
    strcpy(new_user->profile_pic, "");
    new_user->first_post = NULL;
    for (int i = 0; i < MAX_FRIENDS; i++){
        new_user->friends[i] = NULL;
    }

    // return 1 - already exist
    User *list_of_user = *user_ptr_add;
    if(*user_ptr_add != NULL){
        while (list_of_user != NULL){
            //find exist
           if (strcmp(list_of_user->name, name) == 0){
                return 1;
            }else{
                list_of_user = list_of_user->next;}
        }
    }
    
    //return 0 successful -not exist
    if (*user_ptr_add == NULL){
        *user_ptr_add = new_user;
    }else{
        //find last user in orginal list
        list_of_user = *user_ptr_add;
        while (list_of_user->next != NULL){
            list_of_user = list_of_user->next;
        }
        list_of_user->next = malloc(sizeof(User));
        if (list_of_user->next == NULL){
            printf("No enough memory\n");
            exit(3);
        }else{list_of_user->next = new_user;}}

    return 0;
}


/*
 * Return a pointer to the user with this name in
 * the list starting with head. Return NULL if no such user exists.
 *
 * NOTE: You'll likely need to cast a (const User *) to a (User *)
 * to satisfy the prototype without warnings.
 */
User *find_user(const char *name, const User *head) {
    User *current = (User *)head;
    while (current != NULL){
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}


/*
 * Print the usernames of all users in the list starting at curr.
 * Names should be printed to standard output, one per line.
 */
void list_users(const User *curr) {
    User *node = (User *)curr;
    printf("User List\n");
    while (node != NULL){
        printf("\t%s\n", node->name);
        node = node->next;
    }
}


/*
 * Change the filename for the profile pic of the given user.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the file does not exist or cannot be opened.
 *   - 2 if the filename is too long.
 */
int update_pic(User *user, const char *filename) {
    //return 2-too long
    if (filename == NULL||strlen(filename) >= MAX_NAME){
        return 2;
    }

    FILE *file;
    file = fopen(filename, "r");
    
    //return 1 - if the file does not exist or cannot be opened
    if(file == NULL){
        return 1;
    }
    if (fclose(file)!= 0){
        return 1;
    }
    // return 0 - on success
    strcpy(user->profile_pic, filename);
    return 0;
}


/*
 * Make two users friends with each other.  This is symmetric - a pointer to
 * each user must be stored in the 'friends' array of the other.
 *
 * New friends must be added in the first empty spot in the 'friends' array.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the two users are already friends.
 *   - 2 if the users are not already friends, but at least one already has
 *     MAX_FRIENDS friends.
 *   - 3 if the same user is passed in twice.
 *   - 4 if at least one user does not exist.
 *
 * Do not modify either user if the result is a failure.
 * NOTE: If multiple errors apply, return the *largest* error code that applies.
 */
int make_friends(const char *name1, const char *name2, User *head) {
    User *first = find_user(name1, head);
    User *second = find_user(name2, head);
    //at least one user does not exist 
    if(first == NULL||second == NULL){
        return 4;
    }
    //the same user is passed in twice
    if(strcmp(name1, name2) == 0){
        return 3;
    }
    //the two users are already friends - use check_friend_helper
    if (check_friend_helper(first, second) == 2){
        return 1;
    }

    //if the users are not already friends, but at least one already has MAX_FRIENDS friends.
    int count_first = 0, count_second = 0;
    while(first->friends[count_first] != NULL){
        count_first ++;
    }
    while(second->friends[count_second] != NULL){
        count_second ++;
    }
    if(count_first == MAX_FRIENDS ||count_second == MAX_FRIENDS){
        return 2;
    }
    // on success
    first->friends[count_first] = second;
    second->friends[count_second] = first;
    return 0;
}


/*
 * Print a user profile.
 * For an example of the required output format, see the example output
 * linked from the handout.
 * Return:
 *   - 0 on success.
 *   - 1 if the user is NULL.
 */
int print_user(const User *user) {
    //return 1 - if the user is NULL
    if(user == NULL){
        return 1;
    }
    // print profile picture
    FILE *f = fopen(user->profile_pic, "r");
    if(f != NULL){
        //printf("\n");
        char line = fgetc(f);
        while(line != EOF){
            printf("%c", line);
            line = fgetc(f);
        }
        fclose(f);
        printf("\n");
    }

    // print name 
    printf("Name: %s\n", user->name);
    printf("------------------------------------------\n");

    // print friend
    printf("Friends:\n");
    for(int i = 0; i < MAX_FRIENDS; i++){
        while(user->friends[i] != NULL){
            printf("%s\n", user->friends[i]->name);
            i ++;
        }
    }
    printf("------------------------------------------\n");

    // print posts
    printf("Posts:\n");
    Post* node = user->first_post;
    while(node != NULL){
        printf("From: %s\n", node->author);
        printf("Date: %s", ctime(node->date));
        printf("\n%s\n", node->contents);
        if(node->next != NULL){
            printf("\n===\n\n");
        }
        node = node->next;    
    }
    printf("------------------------------------------\n");
    return 0;
}


/*
 * Make a new post from 'author' to the 'target' user,
 * containing the given contents, IF the users are friends.
 *
 * Insert the new post at the *front* of the user's list of posts.
 *
 * 'contents' is a pointer to heap-allocated memory - you do not need
 * to allocate more memory to store the contents of the post.
 *
 * Return:
 *   - 0 on success
 *   - 1 if users exist but are not friends
 *   - 2 if either User pointer is NULL
 */
int make_post(const User *author, User *target, char *contents) {
    //return 2 if either User pointer is NULL
    if(author == NULL || target == NULL){
        return 2;
    }
    //return 1 if users exist but are not friends - use check_friend_helper
    if(check_friend_helper((User*)author, target) != 2){
        return 1;
    }
    // return 0 on success
    Post* new_post = malloc(sizeof(Post));
    if(new_post == NULL){
        printf("No enough memory for new post");
        exit(3); 
    }else{
        new_post->contents = contents;
        strcpy(new_post->author, author->name);
        new_post->date = malloc(sizeof(time_t));
        if(new_post->date == NULL){
            printf("No enough memory for new post");
            exit(3); }
        time(new_post->date);
        new_post->next = target->first_post;
        target->first_post = new_post;
    }
    return 0;
}


/*
 * From the list pointed to by *user_ptr_del, delete the user
 * with the given name.
 * Remove the deleted user from any lists of friends.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if a user with this name does not exist.
 */
int delete_user(const char *name, User **user_ptr_del) {
    User* needdelete = find_user(name, *user_ptr_del);
    // - 1 if a user with this name does not exist.
    if(needdelete == NULL || *user_ptr_del ==NULL){
        return 1;
    }
    // - 0 on success.
    //if this user is the head
    User *temp = *user_ptr_del;
    if(needdelete == *user_ptr_del){
        *user_ptr_del = (*user_ptr_del)->next;
    }else{
        //if this user is not the head 
        User *curr = *user_ptr_del;
        while(curr->next != NULL){
            if(curr->next == needdelete){
                temp = curr->next;
                curr->next = curr->next->next;
                break;
            }else{
                curr = curr->next;
            }
        }
    }
    temp = *user_ptr_del;
    while(temp!=NULL){
        update_friend_helper(needdelete, temp);
        temp = temp->next;
    }
    //free memory
    Post *first = needdelete->first_post;
    while(first != NULL){
        Post *temp_post = first;
        first = first->next;
        free(temp_post->date);
        free(temp_post->contents);
        free(temp_post);
    }
    free(needdelete);
    return 0;
}

/* 
* check if first user and second user are friends.
* Return:
*   - 0 means not already friends; 
    - 2 means both friends
*/
int check_friend_helper(User* first, User* second){
   
   int already_friend = 0; 
    //check name2 in first_user's friend list
    for (int i = 0; i < MAX_FRIENDS; i++){
        if(first->friends[i] != NULL){
            if (first->friends[i] == second){
                already_friend += 1;
                break;
            }
        }else{
            break;
        }
    }
    //check name2 in first_user's friend list
    for (int i = 0; i < MAX_FRIENDS; i++){
        if(second->friends[i] != NULL){
            if (second->friends[i] == first){
                already_friend += 1;
                break;
            }
        }else{
            break;
        }
    }
    return already_friend;
}
/*
* delete this user from his friends's -> friends list
* 
*/
void update_friend_helper(User *delete, User *temp){

    for(int i = 0; i < MAX_FRIENDS; i++){
        while(temp->friends[i] !=  NULL){
            if(temp->friends[i] == delete){
                for(int j = i; j < MAX_FRIENDS-1; j++){
                    temp->friends[j] = temp->friends[j+1];
                }
                temp->friends[MAX_FRIENDS-1] = NULL;
            }
              i++;
        }
    }  
}