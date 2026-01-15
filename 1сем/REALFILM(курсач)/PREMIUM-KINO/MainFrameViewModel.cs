using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Toolkit.Mvvm.Input;
using REALFILM.EFCore.Entities;

namespace REALFILM
{
    public class MainFrameViewModel
    {
        public ObservableCollection<Movie> movies { get; set; }//уведомляет об изменениях в коллекции

        private static List<Movie> listStatic;

        public MainFrameViewModel()
        {
            movies = new ObservableCollection<Movie>(listStatic);
        }

        //все фильмы из БД
        public static void getInfo()
        {
            listStatic = MovieContext.getAllMovies();
        }
    }
}
