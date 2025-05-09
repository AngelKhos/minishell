#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_uwu
{
	char *key;
	char *value;
	struct s_uwu *left;
	struct s_uwu *right;
	/* Potentially add *parent */
} t_uwu;

void printenv(char **envp)
{
	for (size_t i = 0; envp[i]; i++)
	{
		printf("%s\n", envp[i]);
	}
}

t_uwu *create_leaf(char *envstr)
{
	/* TODO */
}

t_uwu *insert_leaf(t_uwu *node, t_uwu *leaf)
{
	/* TODO, recursive */
}

t_uwu *search_leaf(t_uwu *root, char *key)
{
	/* TODO */
}

void destroy_tree(t_uwu *root)
{
	if (!root)
		return ;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root->key);
	free(root->value);
	free(root);
}

char **tree_to_envp(t_uwu *root)
{
	/* TODO */
}

int main(int argc, char **argv, char **envp)
{
	char *str = "OUI=ALED";
	char *adr = strchr(str, '=');
	if (adr)
	{
		char *value = strdup(adr + 1);
		*adr = '\0';
	}
	char *key = strdup(str);

	printenv(envp);
	return (0);
}