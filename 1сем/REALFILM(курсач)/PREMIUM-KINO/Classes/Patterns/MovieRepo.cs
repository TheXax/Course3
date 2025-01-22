using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using Microsoft.Data.SqlClient;
using Microsoft.EntityFrameworkCore;
using REALFILM.EFCore;
using REALFILM.EFCore.Entities;



namespace REALFILM.Classes
{
    public class MovieRepo
    {
        private DBContext context;

        public MovieRepo() => context = new DBContext();



        public List<Movie> GetAllMovies()
        {
            try
            {
                context.Movie.Load(); //загрузка в локальный кэш
                return context.Movie.Local.ToList();
            }
            catch
            {
                return new List<Movie>();
            }
        }


        //получение фильма по заголовку
        public Movie GetMovie(Movie title)
        {
            try
            {
                var ret = context.Movie.FirstOrDefault(x => x.Title == title.Title);
                return ret;
            }
            catch
            {
                return null;
            }
        }



        public bool AddMovie(Movie movie)
        {
            try
            {
                context.Movie.Add(movie);
                context.SaveChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }



        public void DeleteMovie(Movie movie)
        {
            try
            {
                context.Remove(movie);
                context.SaveChanges();
            }
            catch { }
        }


        //удаление фильма и связанного с ним расписания
        public bool DeleteMovieAndSchedule(Movie edit, Movie select)
        {
            try
            {
                var id = new SqlParameter("@id", edit.Id);//sql-параметр для запроса
                context.Database.ExecuteSqlRaw("delete from SCHEDULE where ID_MOVIE = @id", id);
                context.Movie.Remove(select);
                context.SaveChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }



        public bool UpdateRating(UserOrder order, int rate)
        {
            try
            {
                context.Movie.Load();
                var title_movie = new SqlParameter("@title_movie", order.Title);//пар-тр для заголовка фильма
                var rating = new SqlParameter("@rating", rate);
                context.Database.ExecuteSqlRaw("update MOVIE set RATING = round((RATING * ((select count(*) from USERS) - 1) " +
                    " + @rating) / (select count(*) from USERS), 2) where TITLE = @title_movie", title_movie, rating);
                context.SaveChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
