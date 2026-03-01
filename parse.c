#include "cub3d.h"
//Ignore all leading whitespaces.
//If the current row is the 0th row or the final row, only accept '1's and ' 's.
//else, The first and final character should always be a '1'.
//In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
//If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
//If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be '1'
//copilot was filling some of this in but I made sure to understand it and that it followed the map requirements, so I kept it. I also added some additional checks to make sure we have a map to validate and that we skip leading whitespace before checking the other conditions.
int valid_map(t_map map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < map.height)
    {
        while (j < map.width)
        {
            //make sure we have a map to validate
            if (map.height < 1 || map.width < 1)
                return (0);
            //skip leading whitespace
            while(map.map[i][j] == ' ')
                j++;
            //check that first and last row in map only contains '1's and ' 's
            if ((i == 0 || i == map.height - 1) && map.map[i][j] != '1' && map.map[i][j] != ' ')
                return (0);
            if (j == 0 || j == map.width - 1)
            {
                if (map.map[i][j] != '1')
                    return (0);
            }
            //In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
            if(map.map[i][j] == ' ')
            {
                if (map.map[i][j - 1] != '1' && map.map[i][j - 1] != ' ') //one character before current space should be '1' or ' '
                    return (0);
                if (map.map[i][j + 1] != '1' && map.map[i][j + 1] != ' ') //one character after current space should be '1' or ' '
                    return (0);
                if ((i > 0 && (map.map[i - 1][j] != '1' && map.map[i - 1][j] != ' ')) || 
                    (i < map.height - 1 && (map.map[i + 1][j] != '1' && map.map[i + 1][j] != ' ')))
                    return (0);//check if spot above and below is '1' or ' ' amd we are not on the first or last row
            }
            //make sure to use ft_strlen
            //If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1' (else we are exposing a hole in the map)
            if (strlen(map.map[i]) > strlen(map.map[i - 1]) && j > strlen(map.map[i - 1]) && map.map[i][j] != '1')
                return (0);
            //If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be '1'
            if (strlen(map.map[i]) > strlen(map.map[i + 1]) && j > strlen(map.map[i + 1]) && map.map[i][j] != '1')
                return (0);
            j++;
        }
        j = 0;
        i++;
    }
}

//step 1
//store the values so that we can use them later
//step 2

int parse_cub(char *line /*, all things imma need*/)
{
    int i;
    i = 0;
    while (line[i] == ' ')
    {
        i++;
        if (line[i] == '\0' /*&& map array isnt empty return - if it isnt empty store this in the map and then return for next line*/)
            return (0); //empty line, so we can ignore and move on to parsing next thing
        if (line[i] == '1') //we have reached the map, so we can stop parsing the config and move on to parsing the map. We also want to make sure that we actually have a map to parse and that we dont just have a line with spaces and then end of line, because that would mean we have no map
        {
            //start storing in map struct starting from this line
            //store leading white spaces
            //figure out map width and height as we are storing in struct
                //so keep store this and then compare it with each additional line        
                //using INTMAX or something is usuful to make sure we find something
        }
    } //check if we find any 1s becasue we dont want to skip them
    if (line[i] == 'N' && line[i + 1] == 'O')
    {
        //ensure that we dont already have a NO texture path stored in the struct, if we do return error
        //also at end I should be checking that we have a texture for all directions plus floor and ceiling colors
        //have a function where we use mlx_xpm_file_to_image to load the texture from the path specified in the config file
        //then if open have a function wich stores the texture and the NO etc in the struct - this function I should be able to pass it NO, and texture path and it does the rest - therefor it can be used for all sides of the map
        //repeat for all 4 sides and then for floor and ceiling colors
    }
    else if (line[i] == 'S' && line[i + 1] == 'O')
    {
        //parse south texture path and store in t_config struct
    }
    else if (line[i] == 'W' && line[i + 1] == 'E')
    {
        //parse west texture path and store in t_config struct
    }
    else if (line[i] == 'E' && line[i + 1] == 'A')
    {
        //parse east texture path and store in t_config struct
    }
    else if (line[i] == 'F')
    {
        //this is where I am calling the check floor values function
        //if I get the ok that it is valid then I can store the color else return error
        //repeat for ceiling color
    }
    else if (line[i] == 'C')
    {
        //parse ceiling color and store in t_config struct
    }
    
}

int open_cub(void)
{
    int fd;
    char *line;
    fd = open("maps/map.cub", O_RDONLY);
    if (fd < 0)    {
        printf("Error: Could not open file\n");
        return (0);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        //parse line and store in t_parser struct
        //this will involve parsing the texture paths and colors and storing them in the t_config struct within the t_parser struct
        //int parse_cub(char *line /*, all things imma need*/)
        //this is where we are calling the parse_cub function that I am still working on
        free(line);
    }
    close(fd);
    return (1);
}
