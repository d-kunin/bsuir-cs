using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using eBookKeeper.Model;

namespace eBookKeeper
{
    public partial class MainWindow : Window
    {
        public ILibraryIndex Index { get; set; }
        public ObservableCollection<Book> Books { get; set; } 


        public MainWindow()
        {
            InitializeComponent();
            Index = new StubLibraryIndex();

            var index = Index.Restore();
            if (index == null)
                StubLibraryIndex.PopulateWithStubData(Index);
            else
                Index = index;

            Index.AllBooks.Sort();
            DataContext = this;

            Books = new ObservableCollection<Book>(Index.AllBooks);
        }

        protected override void OnClosed(EventArgs e)
        {
            Index.Save();
            base.OnClosed(e);
        }

        private void SearchBox_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            string newText = SearchBox.Text;

            var result = Index.Find(x => x.Title.ToLower().Contains(newText.ToLower()));
            result.Sort();
            BooksList.ItemsSource = result;
        }
    }
}
