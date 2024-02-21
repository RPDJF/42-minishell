/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   betterft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:19:26 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BETTERFT_H
# define BETTERFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct s_garbcol
{
	void				*content;
	struct s_garbcol	*next;
	struct s_garbcol	*previous;
}					t_garbcol;

//		GARBAGE COLLECTOR
//	getgarbage: Retrieves a pointer to a static garbage collector.
//	Returns NULL if the allocation fails.
t_garbcol	**getgarbage(void);
//	gfree: Frees the memory at the specified 'address' and removes it from the
//	garbage collector.
void		gfree(void *address);
//	addgarbage: Adds a pointer 'address' to the garbage collector.
//	Use this function only when allocating with non-betterft functions.
//	Returns the 'address'.
void		*addgarbage(void *address);
//	galloc: Returns a null-filled allocation of 'size' bytes.
//	The allocation address is added to the garbage collector.
void		*galloc(size_t size);
//	cleargarbage: Frees all memory allocated in the garbage collector and clears
//	the collector itself.
void		cleargarbage(void);

//		GARBAGE UTILS

//	lastgarbage: Gets a pointer to the last garbage from a garbage collector.
t_garbcol	*lastgarbage(t_garbcol *garb);

//		REVISITED LIBFT

//	ft_atoi: Converts the initial portion of the string 'str' to its integer
//	representation.
int			ft_atoi(const char *str);
//	ft_atoi_base: Converts the initial portion of the base string 'str' to its
//	integer representation.
int			ft_atoi_base(const char *str, const char *base);
//	ft_bzero: Fills the memory at location 's' with NULL values for the first
//	'n' bytes.
void		ft_bzero(void *s, size_t n);
//	ft_calloc: Allocates memory for an array of 'count' elements, each of size
//	'size'.
//	Initializes the allocated memory to NULL.
void		*ft_calloc(size_t count, size_t size);
//	ft_isalnum: Checks if the given character 'c' is an alphanumeric character.
int			ft_isalnum(int c);
//	ft_isalpha: Checks if the given character 'c' is an alphabetic character.
int			ft_isalpha(int c);
//	ft_isascii: Checks if the given integer 'c' is a valid ASCII character.
int			ft_isascii(int c);
//	ft_isdigit: Checks if the given character 'c' is a digit character.
int			ft_isdigit(int c);
//	ft_isprint: Checks if the given character 'c' is a printable character.
int			ft_isprint(int c);
//	ft_isspace: Checks if the given character 'c' is a space character.
int			ft_isspace(char c);
//	ft_itoa_base_un: Converts the unsigned long number 'n' into a string with a
//	specific base.
char		*ft_itoa_base_un(unsigned long n, const char *base);
//	ft_itoa_base: Converts the int number 'n' into a string with a specific
//	base.
char		*ft_itoa_base(int n, const char *base);
//	ft_itoa_un: Converts the unsigned int number 'n' into a string.
char		*ft_itoa_un(unsigned long n);
//	ft_itoa: Converts the int number 'n' into a string.
char		*ft_itoa(int n);
//	ft_memchr: Returns a pointer to the first occurrence of the specific byte
//	'c'
//	in memory 's'.
//	Returns NULL if no occurrence is found within the first 'n' bytes.
void		*ft_memchr(const void *s, int c, size_t n);
//	ft_memcmp: Compares the first 'n' bytes of memory 's1' and 's2'.
//	Returns the difference between the first pair of differing bytes.
int			ft_memcmp(const void *s1, const void *s2, size_t n);
//	ft_memcpy: Fills the memory at 'dest' with values from 'src' until the size
//	'n' is reached.
//	Overlapping memory regions are not supported.
void		*ft_memcpy(void *dest, const void *src, size_t n);
//	ft_memmove: Fills the memory at 'dest' with values from 'src' until the size
//	'n' is reached.
//	Supports overlapping memory regions.
void		*ft_memmove(void *dest, const void *src, size_t n);
//	ft_memset: Fills the memory at location 's' with the value 'c' for the first
//	'n' bytes.
void		*ft_memset(void *s, int c, size_t n);
//	ft_memsuperclear: Frees references in the 'm' array and clears the memory
//	itself for a total size of 'size'.
void		ft_memsuperclear(void **m, size_t size);
//	ft_absol: Returns the absolute value of the integer 'nb'.
int			ft_absol(int nb);
//	ft_max: Returns the largest integer value between 'nb1' and 'nb2'.
int			ft_max(int nb1, int nb2);
//	ft_min: Returns the smallest integer value between 'nb1' and 'nb2'.
int			ft_min(int nb1, int nb2);
//	ft_printf: Produces output according to a format string 'format'.
int			ft_printf(const char *format, ...);
//	ft_putchar_fd: Writes the character 'c' to the specified file descriptor
//	'fd'.
void		ft_putchar_fd(char c, int fd);
//	ft_putendl_fd: Writes the string 's' followed by a newline to the specified
//	file descriptor 'fd'.
void		ft_putendl_fd(char *s, int fd);
//	ft_putnbr_base: Writes the integer 'n' to the specified file descriptor 'fd'
//	using
//	the specified 'base'.
void		ft_putnbr_base(int n, char *base, int fd);
//	ft_putnbr_fd: Writes the integer 'n' to the specified file descriptor 'fd'.
void		ft_putnbr_fd(int n, int fd);
//	ft_putstr_fd: Writes the string 's' to the specified file descriptor 'fd'.
void		ft_putstr_fd(char *s, int fd);
//	ft_split: Splits the string 's' into substrings using the specified
//	separator 'c'.
//	Returns an array of strings, terminated by NULL, allocated with malloc.
char		**ft_split(char const *s, char c);
//	ft_countwords: Counts the number of words in the string 's' separated by the
//	character 'c'.
size_t		ft_countwords(char const *s, char c);
//	ft_strchr: Searches for the first occurrence of character 'c' in the string
//	's' and returns its address.
char		*ft_strchr(const char *s, int c);
//	ft_strdup: Returns a dynamically allocated copy of the string 'src'.
char		*ft_strdup(const char *src);
//	ft_striteri: Applies the function 'f' to each character of the string 's'
//	along with its index.
char		ft_striteri(char *s, void (*f)(unsigned int, char *));
//	ft_strjoin: Concatenates two strings 's1' and 's2' into a new dynamically
//	allocated string.
char		*ft_strjoin(const char *s1, const char *s2);
//	ft_strlcat: Appends the string 'src' to the end of 'dst', ensuring that the
//	total length does not exceed 'dstsize'.
//	Returns the total length of the string that would have been created if there
//	was enough space.
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
//	ft_strlcpy: Copies the string 'src' to 'dst', ensuring that 'dst' is
//	null-terminated and the total length does not exceed 'size'.
//	Returns the length of the string that would have been copied if there was
//	enough space.
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
//	ft_strlen: Returns the length of the string 'str'.
size_t		ft_strlen(const char *str);
//	ft_strmapi: Applies the function 'f' to each character in the string 's',
//	creating a new string with the results.
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//	ft_strncat: Concatenates at most 'n' characters from the 'src' string onto
//	the end of the 'dest' string.
//	The 'start' parameter indicates the starting index in the 'dest' string
//	where the concatenation should begin.
//	The resulting string is null-terminated.
//	Returns a pointer to the destination string.
char		*ft_strncat(char *dest, const char *src, size_t nb);
//	ft_strncmp: Compares the first 'n' characters of strings 's1' and 's2'.
//	Returns 0 if the strings are identical, a positive value if s1 > s2, and
//	a negative value if s1 < s2.
int			ft_strncmp(const char *s1, const char *s2, size_t n);
//	ft_strnstr: Searches for the first occurrence of the string 'needle' in 
//	haystack' within the first 'len' characters.
//	Returns a pointer to the first character of the found substring, or NULL
//	if not found.
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
//	ft_strrchr: Searches for the last occurrence of character 'c' in the string
//	's' and returns its address.
char		*ft_strrchr(const char *s, int c);
//	ft_strreplace: Replaces all occurrences of the string 'old' with the string
//	'new' in the string 'src'.
//	Returns a new dynamically allocated string.
char		*ft_strreplace(char *src, char *old, char *new);
//	ft_strtrim: Returns a dynamically allocated string without characters from
//	'set' at the beginning and end of 's1'.
char		*ft_strtrim(const char *s1, const char *set);
//	ft_substr: Returns a dynamically allocated substring of 's' starting from
//	'start' and having a length of 'len'.
char		*ft_substr(char const *s, unsigned int start, size_t len);
//	ft_tolower: Converts the given uppercase character 'c' to its lowercase
//	equivalent.
int			ft_tolower(int c);
//	ft_toupper: Converts the given lowercase character 'c' to its uppercase
//	equivalent.
int			ft_toupper(int c);
//	ft_lstadd: Adds a new element with 'content' directly to the bottom of
//	the linked list 'lst'.
t_list		*ft_lstadd(t_list *lst, void *content);
//      ft_lstaddr: Adds a new element with 'content' directly to the top of
//      the linked list 'lst'.
t_list		*ft_lstaddr(t_list *lst, void *content);
//	ft_lstadd_back: Adds a new element 'new' to the end of the linked list
//	'lst'.
void		ft_lstadd_back(t_list **lst, t_list *new);
//	ft_lstadd_front: Adds a new element 'new' to the start of the linked list
//	'lst'.
void		ft_lstadd_front(t_list **lst, t_list *new);
//	ft_lstclear: Clears the memory of all elements in the list using the 'del'
//	function.
//	Finally, sets the pointer to the list to NULL.
void		ft_lstclear(t_list **lst, void (*del)(void *));
//	ft_lstiter: Applies the function 'f' to each element in the list.
void		ft_lstiter(t_list *lst, void (*f)(void *));
//	ft_lstdelone: Frees the memory occupied by a single element in the list
//	using the 'del' function.
void		ft_lstdelone(t_list *lst, void (*del)(void *));
//	ft_lstlast: Returns a pointer to the last element of the list.
t_list		*ft_lstlast(t_list *lst);
//	ft_lstmap: Applies the function 'f' to each element in the list, creates
//	a new list with the results, and frees the memory of the elements in the
//	original list using the 'del' function.
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
//	ft_lstnew: Allocates and returns a new list element with the specified
//	content.
t_list		*ft_lstnew(void *content);
//	ft_lstsize: Returns the number of elements in the list.
int			ft_lstsize(t_list *lst);
//	ft_lstget: Retrieves the node at the specified index 'idx' in the list.
t_list		*ft_lstget(t_list *lst, size_t idx);
//	ft_lstgetid: Retrieves the index of the given 'node' in the 'list'.
int			ft_lstgetid(t_list *list, t_list *node);
//	ft_lstpop: Deletes the first node in the list and frees its memory using
//	the 'del' function.
t_list		*ft_lstpop(t_list *lst, void (*del)(void *));
//	ft_lstpush: Adds a new node with the specified 'content' to the head of the
//	list.
t_list		*ft_lstpush(t_list *lst, void *content);
//	ft_lstrevrotate: Applies a reversed list rotation, making the last node the
//	first.
t_list		*ft_lstrevrotate(t_list *lst);
//	ft_lstrotate: Applies a list rotation, making the first node the last.
t_list		*ft_lstrotate(t_list *lst);
//	ft_lstswap: Swaps the positions of the first two nodes in the list.
t_list		*ft_lstswap(t_list *lst);
//	ft_reallocf: Extends the memory block at 'ptr' to 'newsize' bytes.
//	The 'ptr' memory block is freed.
//	Returns the pointer to the reallocated memory block.
void		*ft_reallocf(void *ptr, size_t size, size_t newsize);
//	ft_get_next_line: Reads a line from the file descriptor 'fd' and returns
//	it as a dynamically allocated string.
//	Returns NULL at the end of the file or if an error occurs.
char		*ft_get_next_line(int fd);
//	ft_memncat: Concatenates 'nb' bytes from the 'src' memory block starting
//	at 'start' to the 'dest' memory block.
//	Returns a pointer to the destination memory block.
void		*ft_memncat(void *dest, size_t start, void *src, size_t nb);
//	ft_memtostr: Converts a block of memory 'mem' with size 'size' to a
//	dynamically allocated string.
//	Returns the resulting string.
char		*ft_memtostr(void *mem, size_t size);

#endif
