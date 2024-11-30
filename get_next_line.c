/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:19:12 by etorun            #+#    #+#             */
/*   Updated: 2024/11/30 22:14:39 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_line(int fd,char *forever)
{
    char buf[BUFFER_SIZE+1];
    int rd;
    char *temp;
    rd=1;
    
    ft_bzero(buf,BUFFER_SIZE+1);
    while(!(ft_strchr(buf,'\n')) && rd != 0)
    {
        rd=read(fd,buf,BUFFER_SIZE);
        if(rd==0 && forever == NULL)
            return (NULL);
        if(rd < 0)
            return (free(forever),NULL);
        buf[rd]='\0';
        if(!forever)
            forever = ft_calloc(1,1); 
        temp = forever;
        forever = ft_strjoin(forever,buf);
        free(temp);
    }
    return(forever);
}
char *keep_remain(char* forever)
{
    int i;
    char *temp;
    
    i = 0;
    while(forever[i] !='\0')
      {
        if(forever[i] =='\n')
        {temp=forever;
        forever=ft_substr(forever,i+1,ft_strlen(forever) - (i));
        free(temp);
        if(forever[0]=='\0')
            return (free(forever),NULL);
        return(forever);
        }
        i++;
    }
    return (free(forever),NULL);
}
char *line_whr_iam(char *forever)
{
    char *done;
    if(ft_strchr(forever,'\n'))
    {
        done=ft_substr(forever,0,ft_strchr(forever,'\n') - forever+1);
        return (done);
    }
    else
     {
        done=ft_substr(forever,0,ft_strlen(forever));
        return (done);
     }   
}

char *get_next_line(int fd)
{
    static char *forever;
    char *done;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    if(forever!=NULL)
    {
        if(!ft_strchr(forever,'\n'))
                forever = read_line(fd,forever);
    }
    else
        forever = read_line(fd,forever);
    if (!forever)
		return (NULL);
    done=  line_whr_iam(forever);
    forever=keep_remain(forever);
    return (done);
}