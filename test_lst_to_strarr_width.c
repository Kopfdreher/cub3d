#include "includes/cub3d.h"
#include <stdio.h>

void print_strarr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("[%d]: '%s' (len=%zu)\n", i, arr[i], strlen(arr[i]));
		i++;
	}
}

int main(void)
{
	t_list *lst = NULL;
	char **result;
	
	// Test 1: Basic test with varying length strings
	printf("=== Test 1: Varying lengths, width=10 ===\n");
	ft_lstadd_back(&lst, ft_lstnew(strdup("abc")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("hello world")));  // longer than width
	ft_lstadd_back(&lst, ft_lstnew(strdup("xy")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("1234567890")));   // exactly width
	
	result = ft_lst_to_strarr_width(&lst, 10);
	if (result)
	{
		print_strarr(result);
		free_strarr(result);
	}
	else
		printf("ERROR: returned NULL\n");
	
	// Test 2: Strings with newlines
	printf("\n=== Test 2: Strings with newlines, width=8 ===\n");
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(strdup("abc\n")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("test\n")));
	
	result = ft_lst_to_strarr_width(&lst, 8);
	if (result)
	{
		print_strarr(result);
		free_strarr(result);
	}
	else
		printf("ERROR: returned NULL\n");
	
	// Test 3: Empty list
	printf("\n=== Test 3: Empty list ===\n");
	lst = NULL;
	result = ft_lst_to_strarr_width(&lst, 5);
	if (result)
	{
		printf("Empty array created (should be just NULL terminator)\n");
		free_strarr(result);
	}
	else
		printf("ERROR: returned NULL\n");
	
	// Test 4: Width = 0
	printf("\n=== Test 4: Width = 0 ===\n");
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(strdup("test")));
	result = ft_lst_to_strarr_width(&lst, 0);
	if (result)
	{
		print_strarr(result);
		free_strarr(result);
	}
	else
		printf("ERROR: returned NULL\n");
		
	printf("\nAll tests completed!\n");
	return (0);
}
