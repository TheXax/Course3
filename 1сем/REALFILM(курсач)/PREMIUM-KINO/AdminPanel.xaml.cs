using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using Microsoft.Data.SqlClient;
using Microsoft.EntityFrameworkCore;
using REALFILM.Classes;
using REALFILM.EFCore;
using REALFILM.EFCore.Entities;

namespace REALFILM
{
    public partial class AdminPanel : Page
    {
        UnitOfWork context;

        public AdminPanel()
        {
            InitializeComponent();
            var sri = Application.GetResourceStream(new Uri("./Styles/arrow.cur", UriKind.Relative));
            var customCursor = new Cursor(sri.Stream);
            Cursor = customCursor;

            context = new UnitOfWork();
            tableView.ItemsSource = context.MovieRepo.GetAllMovies();//заполнение данными из репозитория фильмов
        }



        // Поиск
        private void searchBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            var searchText = searchBox.Text;
            var listOfFilms = context.MovieRepo.GetAllMovies();
            var listSearch = new List<Movie>();
            var regex = new Regex(@"(\w)*" + searchText + @"(\w*)", RegexOptions.IgnoreCase);

            if (searchBox != null)
            {
                foreach (var movie in listOfFilms)
                {
                    var matchesTitle = regex.Matches(movie.Title);
                    var matchesDir = regex.Matches(movie.Director);
                    if (matchesTitle.Count > 0 || matchesDir.Count > 0)
                        listSearch.Add(movie);
                }
                tableView.ItemsSource = listSearch;
            }
        }



        // Кнопка "Добавить фильм"
        private void addButton_Click(object sender, RoutedEventArgs e)
        {
            AddingFilm film = new AddingFilm();
            film.Show();
            tableView.ItemsSource = context.MovieRepo.GetAllMovies();//обновление списка после добавления
        }


        // Кнопка "Отредактировать"
        private void redactButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                RedactingFilm edit = new RedactingFilm();
                var filmEdit = (Movie)tableView.SelectedItem;//выбранный фильм из списка
                var selectedMovieDB = context.MovieRepo.GetMovie(filmEdit);//фильм из БД
                edit.filmName.Text = filmEdit.Title;
                edit.filmDirector.Text = filmEdit.Director;
                edit.genre.Text = filmEdit.Genre;
                edit.rating.Text = filmEdit.Rating.ToString();
                edit.duration.Text = filmEdit.Duration.ToString();

                context.MovieRepo.DeleteMovieAndSchedule(filmEdit, selectedMovieDB);

                if (tableView.SelectedItem != null)
                    if (edit.ShowDialog() == false)
                    {
                        filmEdit.Id = new Guid();
                        filmEdit.Title = edit.filmName.Text;
                        filmEdit.Director = edit.filmDirector.Text;
                        filmEdit.Genre = edit.genre.Text;
                        filmEdit.Duration = int.Parse(edit.duration.Text);
                        filmEdit.Rating = float.Parse(edit.rating.Text);
                        filmEdit.Photo = edit.preview.Source.ToString();

                        context.MovieRepo.AddMovie(filmEdit);//добавление в репозиторий
                        tableView.ItemsSource = context.MovieRepo.GetAllMovies();//обновление списка
                    }
            }
            catch
            {
                MessageBox.Show("Сначала выберите фильм.", "Ошибка!", MessageBoxButton.OK);
            }
        }



        // Кнопка "Добавить расписание"
        private void addScheduleButton_Click(object sender, RoutedEventArgs e)
        {
            var selectedFilm = (EFCore.Entities.Movie)tableView.SelectedItem;
            if (selectedFilm == null)
                MessageBox.Show("Сначала выберите фильм.", "Ошибка!", MessageBoxButton.OK);
            else
            {
                AddSchedule addSchedule = new AddSchedule(selectedFilm);
                addSchedule.Show();
            }
        }




        // Кнопка "Удалить"
        private void deleteButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var ret = context.MovieRepo.DeleteMovieAndSchedule((Movie)tableView.SelectedItem, (Movie)tableView.SelectedItem);
                if (ret)
                {
                    MessageBox.Show("Фильм удалён.", "Успешно!", MessageBoxButton.OK);
                    tableView.ItemsSource = context.MovieRepo.GetAllMovies();
                }
                else throw new Exception();
            }
            catch
            {
                MessageBox.Show("Сначала выберите фильм.", "Ошибка!", MessageBoxButton.OK);
            }
        }



        // Кнопка "Показать все фильмы"
        private void showButton_Click(object sender, RoutedEventArgs e)
        {
            tableView.ItemsSource = context.MovieRepo.GetAllMovies();
        }




        // Фильтрация
        private void comboBoxFilterSelect_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem selectedBoxItem = comboBoxFilterSelect.SelectedValue as ComboBoxItem;
            string selectedGenre = selectedBoxItem.Content.ToString(); //выбранный жанр
            var regex = new Regex(@"(\w)*" + selectedGenre + @"(\w*)", RegexOptions.IgnoreCase);
            var newList = new List<Movie>();
            var listOfFilms = context.MovieRepo.GetAllMovies();

            foreach (var movie in listOfFilms)
            {
                var matches = regex.Matches(movie.Genre);
                if (matches.Count > 0)
                    newList.Add(movie);
            }
            tableView.ItemsSource = newList;

            if (selectedGenre == "Все жанры" || selectedGenre == "All genres")
                tableView.ItemsSource = listOfFilms;
        }        
    }
}
