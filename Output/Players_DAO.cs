using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

public class Players_DAO : Database
{ 
    public Players_DTO GetById(int id) 
    {
        Players_DTO result = null;
        try
        {
           using (SqlCommand cmd = new SqlCommand())
           {
               cmd.Connection = conn;
               cmd.CommandText = @"SELECT * FROM Players
               WHERE id = @id"; //Implemente sua lógica aqui!

               cmd.Parameters.AddWithValue("@id", id);
               using (SqlDataReader reader = cmd.ExecuteReader())
               {
                   if (reader.Read())
                   {
                       result = new Players_DTO()
                       {
                            player_id = reader["player_id"] != DBNull.Value ? Convert.ToInt32(reader["player_id"]) : default, 
                            username = reader["username"] != DBNull.Value ? Convert.ToString(reader["username"]) : default, 
                            email = reader["email"] != DBNull.Value ? Convert.ToString(reader["email"]) : default, 
                            password = reader["password"] != DBNull.Value ? Convert.ToString(reader["password"]) : default, 
                            created_at = reader["created_at"] != DBNull.Value ? Convert.ToDateTime(reader["created_at"]) : default, 
                            last_login = reader["last_login"] != DBNull.Value ? Convert.ToDateTime(reader["last_login"]) : default, 
                            level = reader["level"] != DBNull.Value ? Convert.ToInt32(reader["level"]) : default, 
                            experience = reader["experience"] != DBNull.Value ? Convert.ToInt16(reader["experience"]) : default, 
                            coins = reader["coins"] != DBNull.Value ? Convert.ToInt64(reader["coins"]) : default, 
                            is_active = reader["is_active"] != DBNull.Value ? Convert.ToBoolean(reader["is_active"]) : default, 
                       };
                   }
               }
           }
        }
        catch (SqlException ex)
        {
           throw ex;
        }
        return result;
    }

    public List<Players_DTO> GetAll() 
    {
        List<Players_DTO> result = new List<Players_DTO>(); 
        try
        {
           using (SqlCommand cmd = new SqlCommand())
           {
               cmd.Connection = conn;
               cmd.CommandText = @"SELECT * FROM Players";

               using (SqlDataReader reader = cmd.ExecuteReader())
               {
                   while (reader.Read())
                   {
                       result.Add(new Players_DTO()
                       {
                            player_id = reader["player_id"] != DBNull.Value ? Convert.ToInt32(reader["player_id"]) : default,
                            username = reader["username"] != DBNull.Value ? Convert.ToString(reader["username"]) : default,
                            email = reader["email"] != DBNull.Value ? Convert.ToString(reader["email"]) : default,
                            password = reader["password"] != DBNull.Value ? Convert.ToString(reader["password"]) : default,
                            created_at = reader["created_at"] != DBNull.Value ? Convert.ToDateTime(reader["created_at"]) : default,
                            last_login = reader["last_login"] != DBNull.Value ? Convert.ToDateTime(reader["last_login"]) : default,
                            level = reader["level"] != DBNull.Value ? Convert.ToInt32(reader["level"]) : default,
                            experience = reader["experience"] != DBNull.Value ? Convert.ToInt16(reader["experience"]) : default,
                            coins = reader["coins"] != DBNull.Value ? Convert.ToInt64(reader["coins"]) : default,
                            is_active = reader["is_active"] != DBNull.Value ? Convert.ToBoolean(reader["is_active"]) : default,
                       });
                   }
               }
           }
        }
        catch (SqlException ex)
        {
           throw ex;
        }
        return result;
    }

    public void Insert(Players_DTO item) 
    {
        try
        {
           using (SqlCommand cmd = new SqlCommand())
           {
               cmd.Connection = conn;
               cmd.CommandText = @"INSERT INTO Players
               (
				player_id,
				username,
				email,
				password,
				created_at,
				last_login,
				level,
				experience,
				coins,
				is_active)
               VALUES
               (
				@player_id,
				@username,
				@email,
				@password,
				@created_at,
				@last_login,
				@level,
				@experience,
				@coins,
				@is_active)";

               cmd.Parameters.AddWithValue("@player_id", item.player_id != null ? item.player_id : default); 
               cmd.Parameters.AddWithValue("@username", item.username != null ? item.username : default); 
               cmd.Parameters.AddWithValue("@email", item.email != null ? item.email : default); 
               cmd.Parameters.AddWithValue("@password", item.password != null ? item.password : default); 
               cmd.Parameters.AddWithValue("@created_at", item.created_at != null ? item.created_at : default); 
               cmd.Parameters.AddWithValue("@last_login", item.last_login != null ? item.last_login : default); 
               cmd.Parameters.AddWithValue("@level", item.level != null ? item.level : default); 
               cmd.Parameters.AddWithValue("@experience", item.experience != null ? item.experience : default); 
               cmd.Parameters.AddWithValue("@coins", item.coins != null ? item.coins : default); 
               cmd.Parameters.AddWithValue("@is_active", item.is_active != null ? item.is_active : default); 
               cmd.ExecuteNonQuery();
           }
        }
        catch (SqlException ex)
        {
           throw ex;
        }
    }

    public void Update(Players_DTO item) 
    {
        try
        {
           using (SqlCommand cmd = new SqlCommand())
           {
               cmd.Connection = conn;
               cmd.CommandText = @"UPDATE Players
               SET
				player_id = @player_id,
				username = @username,
				email = @email,
				password = @password,
				created_at = @created_at,
				last_login = @last_login,
				level = @level,
				experience = @experience,
				coins = @coins,
				is_active = @is_active
               WHERE 1 = 1";// Implemente sua lógica aqui! 

               
               cmd.Parameters.AddWithValue("@player_id", item.player_id != null ? item.player_id : default); 
               cmd.Parameters.AddWithValue("@username", item.username != null ? item.username : default); 
               cmd.Parameters.AddWithValue("@email", item.email != null ? item.email : default); 
               cmd.Parameters.AddWithValue("@password", item.password != null ? item.password : default); 
               cmd.Parameters.AddWithValue("@created_at", item.created_at != null ? item.created_at : default); 
               cmd.Parameters.AddWithValue("@last_login", item.last_login != null ? item.last_login : default); 
               cmd.Parameters.AddWithValue("@level", item.level != null ? item.level : default); 
               cmd.Parameters.AddWithValue("@experience", item.experience != null ? item.experience : default); 
               cmd.Parameters.AddWithValue("@coins", item.coins != null ? item.coins : default); 
               cmd.Parameters.AddWithValue("@is_active", item.is_active != null ? item.is_active : default); 
               cmd.ExecuteNonQuery();
           }
        }
        catch (SqlException ex)
        {
           throw ex;
        }
    }

    public void Delete(int id) 
    {
        try
        {
           using (SqlCommand cmd = new SqlCommand())
           {
               cmd.Connection = conn;
               cmd.CommandText = @"DELETE FROM Players
               WHERE id = @id"; //Implemente sua lógica aqui!

               cmd.Parameters.AddWithValue("@id", id);
               cmd.ExecuteNonQuery();
           }
        }
        catch (SqlException ex)
        {
           throw ex;
        }
    }
} 
