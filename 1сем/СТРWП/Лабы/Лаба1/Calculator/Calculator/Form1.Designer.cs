﻿namespace Calculator
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this._firstNum = new System.Windows.Forms.TextBox();
            this._secondNum = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this._resultField = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // _firstNum
            // 
            this._firstNum.Location = new System.Drawing.Point(94, 61);
            this._firstNum.Name = "_firstNum";
            this._firstNum.Size = new System.Drawing.Size(100, 22);
            this._firstNum.TabIndex = 0;
            // 
            // _secondNum
            // 
            this._secondNum.Location = new System.Drawing.Point(343, 61);
            this._secondNum.Name = "_secondNum";
            this._secondNum.Size = new System.Drawing.Size(100, 22);
            this._secondNum.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(94, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 16);
            this.label1.TabIndex = 2;
            this.label1.Text = "Первое значение";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(340, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(122, 16);
            this.label2.TabIndex = 3;
            this.label2.Text = "Второе значение";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(229, 120);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "Сумма";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.CalculateResult);
            // 
            // _resultField
            // 
            this._resultField.AutoSize = true;
            this._resultField.Location = new System.Drawing.Point(241, 167);
            this._resultField.Name = "_resultField";
            this._resultField.Size = new System.Drawing.Size(44, 16);
            this._resultField.TabIndex = 5;
            this._resultField.Text = "label3";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(539, 450);
            this.Controls.Add(this._resultField);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this._secondNum);
            this.Controls.Add(this._firstNum);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox _firstNum;
        private System.Windows.Forms.TextBox _secondNum;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label _resultField;
    }
}

