/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
struct Node *connect(struct Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    struct Node *current = root;
    struct Node *next = NULL;

    if (current->left != NULL)
    {
        next = current->left;
    }

    while ((current != NULL) && (next != NULL))
    {
        if ((current->left != NULL) && (current->right != NULL))
        {
            current->left->next = current->right;
            if (current->next != NULL)
            {
                current->right->next = current->next->left;
            }
        }

        if (current->next != NULL)
        {
            current = current->next;
        }
        else
        {
            if (next != NULL)
            {
                current = next;
                if (current->left != NULL)
                {
                    // Shoule caution! `C` can not assign a NULL variable. We need to check before assigning it.
                    next = current->left;
                }
                else
                {
                    next = NULL;
                }
            }
            else
            {
                current = NULL;
            }
        }
    }

    return root;
}
