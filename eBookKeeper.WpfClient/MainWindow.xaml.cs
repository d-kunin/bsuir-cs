using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using eBookKeeper.Model;

namespace eBookKeeper
{
    public partial class MainWindow : Window
    {
        private ILibraryIndex _mIndex;

        public MainWindow()
        {
            InitializeComponent();
            _mIndex = new StubLibraryIndex();


            var index = _mIndex.Restore();
            if (index == null)
                StubLibraryIndex.PopulateWithStubData(_mIndex);
            else
                _mIndex = index;

            _mIndex.AllBooks.Sort();
            ResultList.ItemsSource = _mIndex.AllBooks;
        }

        protected override void OnClosed(EventArgs e)
        {
            _mIndex.Save();
            base.OnClosed(e);
        }

        private void SearchBox_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            string newText = SearchBox.Text;

            var result = _mIndex.Find(x => x.Title.Contains(newText));
            result.Sort();
            ResultList.ItemsSource = result;
        }
    }
}
