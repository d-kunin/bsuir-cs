using System;
using System.Collections.ObjectModel;
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
          Index = new LibraryIndexOnDb();

            var index = Index.Restore();
//          StubLibraryIndex.PopulateWithStubData(Index);

            DataContext = this;
            Books = new ObservableCollection<Book>(Index.AllBooks);
        }

        protected override void OnClosed(EventArgs e)
        {
            Index.Save();

            var index = Index as IDisposable;
            if (index != null)
                index.Dispose();

            base.OnClosed(e);
        }

        private void SearchBox_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            string newText = SearchBox.Text;
            var result = Index.Find(x => x.Title.ToLower().Contains(newText.ToLower()));
            result.Sort();
            // could make easier
            Books = new ObservableCollection<Book>(result);
            BooksList.ItemsSource = Books;
        }

        private void RemoveButton_OnClick(object sender, RoutedEventArgs e)
        {
            Book bookToRemove = (Book) BooksList.SelectedItem;

            Index.Delete(bookToRemove);
            Books.Remove(bookToRemove);
        }

        private void AddButton_OnClick(object sender, RoutedEventArgs e)
        {
            Book newBook = Index.CreateBook("New book!");
            Books.Insert(0, newBook); // show recently added items first

            BooksList.SelectedItem = newBook;
        }
      
    }
}
