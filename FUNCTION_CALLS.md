# Function Call Hierarchy - parse_init.c

```mermaid
graph TD
    parse_init["parse_init"]
    parse_cub_file["parse_cub_file"]
    open_cub["open_cub"]
    valid_map["valid_map"]
    
    parse_init --> parse_cub_file
    parse_cub_file --> open_cub
    parse_cub_file --> valid_map
    
    open_cub --> init_cub_errors["init_cub_errors"]
    open_cub --> check_line_for_ws["check_line_for_ws"]
    open_cub --> parse_cub["parse_cub"]
    open_cub --> assign_map_content["assign_map_content"]
    
    parse_cub --> set_config_path["set_config_path"]
    set_config_path --> trim_path_ws["trim_path_ws"]
    
    assign_map_content --> get_map_content["get_map_content"]
    get_map_content --> init_map_list["init_map_list"]
    get_map_content --> add_nodes_to_list["add_nodes_to_list"]
    
    init_map_list --> set_a_b_to_c["set_a_b_to_c"]
    add_nodes_to_list --> set_a_b_to_c
    
    valid_map --> all_chars_valid["all_chars_valid"]
    valid_map --> check_boarder_and_zero["check_boarder_and_zero"]
    
    all_chars_valid --> is_valid_map_char["is_valid_map_char"]
    all_chars_valid --> is_player_char["is_player_char"]
    all_chars_valid --> set_player_orientation["set_player_orientation"]
    
    set_player_orientation --> set_orientation_values["set_orientation_values"]
    
    check_boarder_and_zero --> check_boarders["check_boarders"]
    check_boarder_and_zero --> is_player_char
    check_boarder_and_zero --> check_surrounding_spaces["check_surrounding_spaces"]
    
    style parse_init fill:#90EE90
    style parse_cub_file fill:#87CEEB
    style open_cub fill:#87CEEB
    style valid_map fill:#87CEEB
```

## Key Flow

- **Green**: Entry point `parse_init`
- **Blue**: Three main branches
  - File I/O and config parsing (`open_cub`)
  - Map validation (`valid_map`)
  
- **Configuration parsing**: `parse_cub` → `set_config_path` → `trim_path_ws`
- **Map reading**: `assign_map_content` → `get_map_content` → list management
- **Validation**: Checks for valid characters, boarders, and surrounding spaces
