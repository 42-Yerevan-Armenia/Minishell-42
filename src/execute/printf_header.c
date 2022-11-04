/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:18:59 by arakhurs          #+#    #+#             */
/*   Updated: 2022/10/31 13:42:16 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ph_1(void)
{
	printf("%s%s", RED, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\
	\n");
	printf("@                                                                          @\
	\n");
	printf("%s%s%s%s%s", "@                   ", BLUE, "___________________________________          \
          ", RED, "@\n");
	printf("%s%s%s%s%s", "@                  ", BLUE, "|                                   |         \
          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s", "@                  ", BLUE, "|", YELLOW, "        BORN    TO    CODE\
         ", BLUE, "|", RED, "                   @\n");
	printf("%s%s%s%s%s", "@                  ", BLUE, "|___________________________________|          \
         ", RED, "@\n");
	printf("@                                                                          @\
	\n");
	printf("@                                                                          @\
	\n");
	printf("%s%s%s", "@                       & J^^^^^^^^:~5    7^^^^^^^^^^^^^^^^^^^^J& \
	   ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@                     & Y^", BLUE, \
	"#########", RED, "!G     ^", BLUE, "####################", \
	RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@                   &&P~", \
	BLUE, "#########", RED, "~P&&     ^", BLUE, "#####", RED, "~P&&5", \
	BLUE, "##########", RED, "7&          ", RED, "@\n");
}

void	ph_2(void)
{
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@                  &G!", \
	BLUE, "#########", RED, "^5 &       ^", BLUE, "###", RED, "^5 & &5", \
	BLUE, "##########", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@                &B7", \
	BLUE, "#########", RED, ":Y^&         ^", BLUE, "#", RED, ":Y &   &5", \
	BLUE, "##########", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@              & J", BLUE, \
	"########", RED, ".J&             !?&      &5", BLUE, \
	"##########", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@            & Y:", BLUE, \
	"########", RED, ".?B&              &     &^Y:", BLUE, \
	"#########", RED, "7B           ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@          &&5^", BLUE, \
	"#########", RED, "!G&&                   &&P^", BLUE, \
	"#########", RED, "~P&            ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@        &&P~", BLUE, \
	"#########", RED, "~P&&                    &G!", BLUE, \
	"#########", RED, "^5 &             ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@       &G7", BLUE, \
	"#########", RED, "^5 &                    &B7.", BLUE, \
	"########", RED, ":Y &               ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     &B?.", BLUE, \
	"########", RED, ":Y&                     &B?.", BLUE, \
	"########", RED, ".JB&                 ", RED, "@\n");
}

void	ph_3(void)
{
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y:", BLUE, \
	"#########", RED, "^YPP5555555555555555P    Y:", BLUE, \
	"#########", RED, "7B&     & B           ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y:", BLUE, \
	"#############################\
", RED, "^    ^", BLUE, "#########", RED, \
": &    & P^7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y:", BLUE, "#####################\
########", RED, "^    ^", BLUE, "#########", RED, \
":     &G!", BLUE, "##", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y:", BLUE, "#####################\
########", RED, "^    ^", BLUE, "#########", RED, \
":   &G7", BLUE, "####", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y:", BLUE, "#####################\
########", RED, "^    ^", BLUE, "#########", RED, \
": &B?.", BLUE, "#####", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@     Y????????????????????\
:", BLUE, "#########", RED, "^    ^", BLUE, "#########", RED, ".BJ.", \
BLUE, "#######", RED, "7&          ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s", RED, "@                          ^", \
BLUE, "#########", RED, "^    ^", BLUE, "###################", \
RED, "7&           ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s", RED, "@                          ^", BLUE, \
"#########", RED, "^    J77777777777777777777            ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s", RED, "@                          ^", BLUE, \
"#########", RED, "^                                     ", RED, "@\n");
}

void	printf_header(void)
{
	ph_1();
	ph_2();
	ph_3();
	printf("%s%s%s%s%s%s%s%s%s", "@     ", BLUE, \
" _____________", RED, "       ^", BLUE, \
"#########", RED, "^                                     @\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "@     ", BLUE, "|      \
	    ", BLUE, "|", RED, "      ^", BLUE, "#########", RED, ":  \
    ", BLUE, "___________________            ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", "@     ", BLUE, "|", YELLOW, \
" By vaghazar ", BLUE, "|", RED, "      P555555555P     ", BLUE, \
"|                   |           ", RED, "@\n");
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", "@     ", BLUE, "|", YELLOW, \
" By arakhurs ", BLUE, "|                      |", YELLOW, \
"  YEREVAN ARMENIA  ", BLUE, "|           ", RED, "@\n");
	printf("%s%s%s%s%s%s%s", "@     ", BLUE, "|_____________", BLUE, "|                      \
|___________________|           ", RED, "@\n");
	printf("%s%s", RED, "@                                                                          @\
\n");
	printf("@                                                                          @\
\n");
	printf("%s%s", "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\
\n", WHITE);
}
